/*!
 * \file galileo_e1_dll_pll_veml_tracking_cc.cc
 * \brief Implementation of a code DLL + carrier PLL VEML (Very Early
 *  Minus Late) tracking block for Galileo E1 signals
 * \author Luis Esteve, 2012. luis(at)epsilon-formacion.com
 *
 * Code DLL + carrier PLL according to the algorithms described in:
 * [1] K.Borre, D.M.Akos, N.Bertelsen, P.Rinder, and S.H.Jensen,
 * A Software-Defined GPS and Galileo Receiver. A Single-Frequency
 * Approach, Birkhauser, 2007
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2017  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#include "galileo_e1_dll_pll_veml_tracking_cc.h"
#include "galileo_e1_signal_processing.h"
#include "tracking_discriminators.h"
#include "lock_detectors.h"
#include "Galileo_E1.h"
#include "control_message_factory.h"
#include "gnss_sdr_flags.h"
#include <boost/lexical_cast.hpp>
#include <gnuradio/io_signature.h>
#include <glog/logging.h>
#include <matio.h>
#include <volk_gnsssdr/volk_gnsssdr.h>
#include <cmath>
#include <iostream>
#include <memory>
#include <sstream>

using google::LogMessage;

galileo_e1_dll_pll_veml_tracking_cc_sptr
galileo_e1_dll_pll_veml_make_tracking_cc(
    long if_freq,
    long fs_in,
    unsigned int vector_length,
    bool dump,
    std::string dump_filename,
    float pll_bw_hz,
    float dll_bw_hz,
    float pll_bw_narrow_hz,
    float dll_bw_narrow_hz,
    float early_late_space_chips,
    float very_early_late_space_chips,
    float early_late_space_narrow_chips,
    float very_early_late_space_narrow_chips,
    int extend_correlation_symbols,
    bool track_pilot)
{
    return galileo_e1_dll_pll_veml_tracking_cc_sptr(new galileo_e1_dll_pll_veml_tracking_cc(if_freq,
        fs_in,
        vector_length,
        dump,
        dump_filename,
        pll_bw_hz,
        dll_bw_hz,
        pll_bw_narrow_hz,
        dll_bw_narrow_hz,
        early_late_space_chips,
        very_early_late_space_chips,
        early_late_space_narrow_chips,
        very_early_late_space_narrow_chips,
        extend_correlation_symbols,
        track_pilot));
}


void galileo_e1_dll_pll_veml_tracking_cc::forecast(int noutput_items,
    gr_vector_int &ninput_items_required)
{
    if (noutput_items != 0)
        {
            ninput_items_required[0] = static_cast<int>(d_vector_length) * 2;  //set the required available samples in each call
        }
}


galileo_e1_dll_pll_veml_tracking_cc::galileo_e1_dll_pll_veml_tracking_cc(
    long if_freq,
    long fs_in,
    unsigned int vector_length,
    bool dump,
    std::string dump_filename,
    float pll_bw_hz,
    float dll_bw_hz,
    float pll_bw_narrow_hz,
    float dll_bw_narrow_hz,
    float early_late_space_chips,
    float very_early_late_space_chips,
    float early_late_space_narrow_chips,
    float very_early_late_space_narrow_chips,
    int extend_correlation_symbols,
    bool track_pilot) : gr::block("galileo_e1_dll_pll_veml_tracking_cc", gr::io_signature::make(1, 1, sizeof(gr_complex)),
                            gr::io_signature::make(1, 1, sizeof(Gnss_Synchro)))
{
    // Telemetry bit synchronization message port input
    this->message_port_register_in(pmt::mp("preamble_timestamp_s"));
    this->set_relative_rate(1.0 / vector_length);

    this->message_port_register_out(pmt::mp("events"));

    // initialize internal vars
    d_dump = dump;
    d_if_freq = if_freq;
    d_fs_in = fs_in;
    d_vector_length = vector_length;
    d_dump_filename = dump_filename;
    d_code_loop_filter = Tracking_2nd_DLL_filter(Galileo_E1_CODE_PERIOD);
    d_carrier_loop_filter = Tracking_2nd_PLL_filter(Galileo_E1_CODE_PERIOD);

    // Initialize tracking  ==========================================

    // Set bandwidth of code and carrier loop filters
    d_dll_bw_hz = dll_bw_hz;
    d_pll_bw_hz = pll_bw_hz;
    d_dll_bw_narrow_hz = dll_bw_narrow_hz;
    d_pll_bw_narrow_hz = pll_bw_narrow_hz;

    d_code_loop_filter.set_DLL_BW(d_dll_bw_hz);
    d_carrier_loop_filter.set_PLL_BW(d_pll_bw_hz);

    // Correlator spacing
    d_early_late_spc_chips = early_late_space_chips;                          // Define early-late offset (in chips)
    d_very_early_late_spc_chips = very_early_late_space_chips;                // Define very-early-late offset (in chips)
    d_early_late_spc_narrow_chips = early_late_space_narrow_chips;            // Define narrow early-late offset (in chips)
    d_very_early_late_spc_narrow_chips = very_early_late_space_narrow_chips;  // Define narrow very-early-late offset (in chips)

    // Initialization of local code replica
    // Get space for a vector with the sinboc(1,1) replica sampled 2x/chip
    d_tracking_code = static_cast<float *>(volk_gnsssdr_malloc((2 * Galileo_E1_B_CODE_LENGTH_CHIPS) * sizeof(float), volk_gnsssdr_get_alignment()));

    // correlator outputs (scalar)
    d_n_correlator_taps = 5;  // Very-Early, Early, Prompt, Late, Very-Late
    d_correlator_outs = static_cast<gr_complex *>(volk_gnsssdr_malloc(d_n_correlator_taps * sizeof(gr_complex), volk_gnsssdr_get_alignment()));
    for (int n = 0; n < d_n_correlator_taps; n++)
        {
            d_correlator_outs[n] = gr_complex(0, 0);
        }
    // map memory pointers of correlator outputs
    d_Very_Early = &d_correlator_outs[0];
    d_Early = &d_correlator_outs[1];
    d_Prompt = &d_correlator_outs[2];
    d_Late = &d_correlator_outs[3];
    d_Very_Late = &d_correlator_outs[4];

    d_local_code_shift_chips = static_cast<float *>(volk_gnsssdr_malloc(d_n_correlator_taps * sizeof(float), volk_gnsssdr_get_alignment()));
    // Set TAPs delay values [chips]
    d_local_code_shift_chips[0] = -d_very_early_late_spc_chips;
    d_local_code_shift_chips[1] = -d_early_late_spc_chips;
    d_local_code_shift_chips[2] = 0.0;
    d_local_code_shift_chips[3] = d_early_late_spc_chips;
    d_local_code_shift_chips[4] = d_very_early_late_spc_chips;

    d_correlation_length_samples = d_vector_length;
    multicorrelator_cpu.init(2 * d_correlation_length_samples, d_n_correlator_taps);

    d_extend_correlation_symbols = extend_correlation_symbols;
    // Enable Data component prompt correlator (slave to Pilot prompt) if tracking uses Pilot signal
    d_track_pilot = track_pilot;
    if (d_track_pilot)
        {
            // extended integration control
            if (d_extend_correlation_symbols > 1)
                {
                    d_enable_extended_integration = true;
                }
            else
                {
                    d_enable_extended_integration = false;
                }
            // Extra correlator for the data component
            d_local_code_data_shift_chips = static_cast<float *>(volk_gnsssdr_malloc(sizeof(float), volk_gnsssdr_get_alignment()));
            d_local_code_data_shift_chips[0] = 0.0;
            correlator_data_cpu.init(2 * d_correlation_length_samples, 1);
            d_Prompt_Data = static_cast<gr_complex *>(volk_gnsssdr_malloc(sizeof(gr_complex), volk_gnsssdr_get_alignment()));
            d_Prompt_Data[0] = gr_complex(0, 0);
            d_data_code = static_cast<float *>(volk_gnsssdr_malloc((2 * Galileo_E1_B_CODE_LENGTH_CHIPS) * sizeof(float), volk_gnsssdr_get_alignment()));
        }
    else
        {
            // Disable extended integration if data component tracking is selected
            d_enable_extended_integration = false;
        }

    //--- Initializations ------------------------------
    // Initial code frequency basis of NCO
    d_code_freq_chips = static_cast<double>(Galileo_E1_CODE_CHIP_RATE_HZ);
    // Residual code phase (in chips)
    d_rem_code_phase_samples = 0.0;
    // Residual carrier phase
    d_rem_carr_phase_rad = 0.0;

    // sample synchronization
    d_sample_counter = 0;
    //d_sample_counter_seconds = 0;
    d_acq_sample_stamp = 0;

    d_current_prn_length_samples = static_cast<int>(d_vector_length);

    // CN0 estimation and lock detector buffers
    d_cn0_estimation_counter = 0;
    d_Prompt_buffer = new gr_complex[FLAGS_cn0_samples];
    d_carrier_lock_test = 1;
    d_CN0_SNV_dB_Hz = 0;
    d_carrier_lock_fail_counter = 0;
    d_carrier_lock_threshold = FLAGS_carrier_lock_th;

    systemName["E"] = std::string("Galileo");

    clear_tracking_vars();

    d_acquisition_gnss_synchro = 0;
    d_channel = 0;
    d_acq_code_phase_samples = 0.0;
    d_acq_carrier_doppler_hz = 0.0;
    d_carrier_doppler_hz = 0.0;
    d_acc_carrier_phase_rad = 0.0;

    d_extend_correlation_symbols_count = 0;
    d_code_phase_step_chips = 0.0;
    d_carrier_phase_step_rad = 0.0;
    d_rem_code_phase_chips = 0.0;
    d_K_blk_samples = 0.0;
    d_code_phase_samples = 0.0;

    d_state = 0;  // initial state: standby
}


void galileo_e1_dll_pll_veml_tracking_cc::start_tracking()
{
    /*
     *  correct the code phase according to the delay between acq and trk
     */
    d_acq_code_phase_samples = d_acquisition_gnss_synchro->Acq_delay_samples;
    d_acq_carrier_doppler_hz = d_acquisition_gnss_synchro->Acq_doppler_hz;
    d_acq_sample_stamp = d_acquisition_gnss_synchro->Acq_samplestamp_samples;

    long int acq_trk_diff_samples;
    double acq_trk_diff_seconds;
    acq_trk_diff_samples = static_cast<long int>(d_sample_counter) - static_cast<long int>(d_acq_sample_stamp);  //-d_vector_length;
    DLOG(INFO) << "Number of samples between Acquisition and Tracking = " << acq_trk_diff_samples;
    acq_trk_diff_seconds = static_cast<float>(acq_trk_diff_samples) / static_cast<float>(d_fs_in);
    // Doppler effect
    // Fd=(C/(C+Vr))*F
    double radial_velocity = (Galileo_E1_FREQ_HZ + d_acq_carrier_doppler_hz) / Galileo_E1_FREQ_HZ;
    // new chip and prn sequence periods based on acq Doppler
    double T_chip_mod_seconds;
    double T_prn_mod_seconds;
    double T_prn_mod_samples;
    d_code_freq_chips = radial_velocity * Galileo_E1_CODE_CHIP_RATE_HZ;
    d_code_phase_step_chips = static_cast<double>(d_code_freq_chips) / static_cast<double>(d_fs_in);
    T_chip_mod_seconds = 1 / d_code_freq_chips;
    T_prn_mod_seconds = T_chip_mod_seconds * Galileo_E1_B_CODE_LENGTH_CHIPS;
    T_prn_mod_samples = T_prn_mod_seconds * static_cast<double>(d_fs_in);

    d_current_prn_length_samples = round(T_prn_mod_samples);

    double T_prn_true_seconds = Galileo_E1_B_CODE_LENGTH_CHIPS / Galileo_E1_CODE_CHIP_RATE_HZ;
    double T_prn_true_samples = T_prn_true_seconds * static_cast<double>(d_fs_in);
    double T_prn_diff_seconds = T_prn_true_seconds - T_prn_mod_seconds;
    double N_prn_diff = acq_trk_diff_seconds / T_prn_true_seconds;
    double corrected_acq_phase_samples, delay_correction_samples;
    corrected_acq_phase_samples = fmod((d_acq_code_phase_samples + T_prn_diff_seconds * N_prn_diff * static_cast<double>(d_fs_in)), T_prn_true_samples);
    if (corrected_acq_phase_samples < 0)
        {
            corrected_acq_phase_samples = T_prn_mod_samples + corrected_acq_phase_samples;
        }
    delay_correction_samples = d_acq_code_phase_samples - corrected_acq_phase_samples;

    d_acq_code_phase_samples = corrected_acq_phase_samples;

    d_carrier_doppler_hz = d_acq_carrier_doppler_hz;
    d_carrier_phase_step_rad = GALILEO_TWO_PI * d_carrier_doppler_hz / static_cast<double>(d_fs_in);

    // DLL/PLL filter initialization
    d_carrier_loop_filter.initialize();  // initialize the carrier filter
    d_code_loop_filter.initialize();     // initialize the code filter

    if (d_track_pilot)
        {
            char pilot_signal[3] = "1C";
            galileo_e1_code_gen_float_sampled(d_tracking_code,
                pilot_signal,
                false,
                d_acquisition_gnss_synchro->PRN,
                Galileo_E1_CODE_CHIP_RATE_HZ,
                0);
            galileo_e1_code_gen_float_sampled(d_data_code,
                d_acquisition_gnss_synchro->Signal,
                false,
                d_acquisition_gnss_synchro->PRN,
                Galileo_E1_CODE_CHIP_RATE_HZ,
                0);
            d_Prompt_Data[0] = gr_complex(0, 0);  // clean data correlator output
            correlator_data_cpu.set_local_code_and_taps(static_cast<int>(Galileo_E1_B_CODE_LENGTH_CHIPS),
                d_data_code,
                d_local_code_shift_chips);
        }
    else
        {
            galileo_e1_code_gen_float_sampled(d_tracking_code,
                d_acquisition_gnss_synchro->Signal,
                false,
                d_acquisition_gnss_synchro->PRN,
                Galileo_E1_CODE_CHIP_RATE_HZ,
                0);
        }

    multicorrelator_cpu.set_local_code_and_taps(static_cast<int>(Galileo_E1_B_CODE_LENGTH_CHIPS), d_tracking_code, d_local_code_shift_chips);
    for (int n = 0; n < d_n_correlator_taps; n++)
        {
            d_correlator_outs[n] = gr_complex(0, 0);
        }

    d_carrier_lock_fail_counter = 0;
    d_rem_code_phase_samples = 0;
    d_rem_carr_phase_rad = 0.0;
    d_rem_code_phase_chips = 0.0;
    d_acc_carrier_phase_rad = 0.0;

    d_code_phase_samples = d_acq_code_phase_samples;

    std::string sys_ = &d_acquisition_gnss_synchro->System;
    sys = sys_.substr(0, 1);

    // DEBUG OUTPUT
    std::cout << "Tracking of Galileo E1 signal started on channel " << d_channel << " for satellite " << Gnss_Satellite(systemName[sys], d_acquisition_gnss_synchro->PRN) << std::endl;
    LOG(INFO) << "Starting tracking of satellite " << Gnss_Satellite(systemName[sys], d_acquisition_gnss_synchro->PRN) << " on channel " << d_channel;

    // enable tracking pull-in
    d_state = 1;

    LOG(INFO) << "PULL-IN Doppler [Hz]=" << d_carrier_doppler_hz
              << " Code Phase correction [samples]=" << delay_correction_samples
              << " PULL-IN Code Phase [samples]=" << d_acq_code_phase_samples;
}


galileo_e1_dll_pll_veml_tracking_cc::~galileo_e1_dll_pll_veml_tracking_cc()
{
    if (d_dump_file.is_open())
        {
            try
                {
                    d_dump_file.close();
                }
            catch (const std::exception &ex)
                {
                    LOG(WARNING) << "Exception in destructor " << ex.what();
                }
        }
    if (d_dump)
        {
            if (d_channel == 0)
                {
                    std::cout << "Writing .mat files ...";
                }
            galileo_e1_dll_pll_veml_tracking_cc::save_matfile();
            if (d_channel == 0)
                {
                    std::cout << " done." << std::endl;
                }
        }
    try
        {
            volk_gnsssdr_free(d_local_code_shift_chips);
            volk_gnsssdr_free(d_correlator_outs);
            volk_gnsssdr_free(d_tracking_code);
            if (d_track_pilot)
                {
                    volk_gnsssdr_free(d_Prompt_Data);
                    volk_gnsssdr_free(d_data_code);
                    volk_gnsssdr_free(d_local_code_data_shift_chips);
                    correlator_data_cpu.free();
                }
            delete[] d_Prompt_buffer;
            multicorrelator_cpu.free();
        }
    catch (const std::exception &ex)
        {
            LOG(WARNING) << "Exception in destructor " << ex.what();
        }
}


bool galileo_e1_dll_pll_veml_tracking_cc::acquire_secondary()
{
    //******* preamble correlation ********
    int corr_value = 0;
    for (unsigned int i = 0; i < Galileo_E1_C_SECONDARY_CODE_LENGTH; i++)
        {
            if (d_Prompt_buffer_deque.at(i).real() < 0)  // symbols clipping
                {
                    if (Galileo_E1_C_SECONDARY_CODE.at(i) == '0')
                        {
                            corr_value++;
                        }
                    else
                        {
                            corr_value--;
                        }
                }
            else
                {
                    if (Galileo_E1_C_SECONDARY_CODE.at(i) == '0')
                        {
                            corr_value--;
                        }
                    else
                        {
                            corr_value++;
                        }
                }
        }

    if (abs(corr_value) == Galileo_E1_C_SECONDARY_CODE_LENGTH)
        {
            return true;
        }
    else
        {
            return false;
        }
}


bool galileo_e1_dll_pll_veml_tracking_cc::cn0_and_tracking_lock_status()
{
    // ####### CN0 ESTIMATION AND LOCK DETECTORS ######
    if (d_cn0_estimation_counter < FLAGS_cn0_samples)
        {
            // fill buffer with prompt correlator output values
            d_Prompt_buffer[d_cn0_estimation_counter] = d_P_accu;
            d_cn0_estimation_counter++;
            return true;
        }
    else
        {
            d_cn0_estimation_counter = 0;
            // Code lock indicator
            d_CN0_SNV_dB_Hz = cn0_svn_estimator(d_Prompt_buffer, FLAGS_cn0_samples, d_fs_in, Galileo_E1_B_CODE_LENGTH_CHIPS);
            // Carrier lock indicator
            d_carrier_lock_test = carrier_lock_detector(d_Prompt_buffer, FLAGS_cn0_samples);
            // Loss of lock detection
            if (d_carrier_lock_test < d_carrier_lock_threshold or d_CN0_SNV_dB_Hz < FLAGS_cn0_min)
                {
                    d_carrier_lock_fail_counter++;
                }
            else
                {
                    if (d_carrier_lock_fail_counter > 0) d_carrier_lock_fail_counter--;
                }
            if (d_carrier_lock_fail_counter > FLAGS_max_lock_fail)
                {
                    std::cout << "Loss of lock in channel " << d_channel << "!" << std::endl;
                    LOG(INFO) << "Loss of lock in channel " << d_channel << "!";
                    this->message_port_pub(pmt::mp("events"), pmt::from_long(3));  // 3 -> loss of lock
                    d_carrier_lock_fail_counter = 0;
                    return false;
                }
            else
                {
                    return true;
                }
        }
}


// correlation requires:
// - updated remnant carrier phase in radians (rem_carr_phase_rad)
// - updated remnant code phase in samples (d_rem_code_phase_samples)
// - d_code_freq_chips
// - d_carrier_doppler_hz
void galileo_e1_dll_pll_veml_tracking_cc::do_correlation_step(const gr_complex *input_samples)
{
    // ################# CARRIER WIPEOFF AND CORRELATORS ##############################
    // perform carrier wipe-off and compute Early, Prompt and Late correlation
    multicorrelator_cpu.set_input_output_vectors(d_correlator_outs, input_samples);
    multicorrelator_cpu.Carrier_wipeoff_multicorrelator_resampler(
        d_rem_carr_phase_rad,
        d_carrier_phase_step_rad,
        d_rem_code_phase_chips,
        d_code_phase_step_chips,
        d_correlation_length_samples);

    // DATA CORRELATOR (if tracking tracks the pilot signal)
    if (d_track_pilot)
        {
            correlator_data_cpu.set_input_output_vectors(d_Prompt_Data, input_samples);
            correlator_data_cpu.Carrier_wipeoff_multicorrelator_resampler(
                d_rem_carr_phase_rad,
                d_carrier_phase_step_rad,
                d_rem_code_phase_chips,
                d_code_phase_step_chips,
                d_correlation_length_samples);
        }
}


void galileo_e1_dll_pll_veml_tracking_cc::run_dll_pll(bool disable_costas_loop)
{
    // ################## PLL ##########################################################
    // PLL discriminator
    if (disable_costas_loop == true)
        {
            // Secondary code acquired. No symbols transition should be present in the signal
            d_carr_error_hz = pll_four_quadrant_atan(d_P_accu) / GALILEO_TWO_PI;
        }
    else
        {
            // Costas loop discriminator, insensitive to 180 deg phase transitions
            d_carr_error_hz = pll_cloop_two_quadrant_atan(d_P_accu) / GALILEO_TWO_PI;
        }

    // Carrier discriminator filter
    d_carr_error_filt_hz = d_carrier_loop_filter.get_carrier_nco(d_carr_error_hz);
    // New carrier Doppler frequency estimation
    d_carrier_doppler_hz = d_acq_carrier_doppler_hz + d_carr_error_filt_hz;
    // New code Doppler frequency estimation
    d_code_freq_chips = Galileo_E1_CODE_CHIP_RATE_HZ + ((d_carrier_doppler_hz * Galileo_E1_CODE_CHIP_RATE_HZ) / Galileo_E1_FREQ_HZ);

    // ################## DLL ##########################################################
    // DLL discriminator
    d_code_error_chips = dll_nc_vemlp_normalized(d_VE_accu, d_E_accu, d_L_accu, d_VL_accu);  // [chips/Ti]
    // Code discriminator filter
    d_code_error_filt_chips = d_code_loop_filter.get_code_nco(d_code_error_chips);  // [chips/second]
}


void galileo_e1_dll_pll_veml_tracking_cc::clear_tracking_vars()
{
    *d_Very_Early = gr_complex(0, 0);
    *d_Early = gr_complex(0, 0);
    *d_Prompt = gr_complex(0, 0);
    *d_Late = gr_complex(0, 0);
    *d_Very_Late = gr_complex(0, 0);
    d_carr_error_hz = 0.0;
    d_carr_error_filt_hz = 0.0;
    d_code_error_chips = 0.0;
    d_code_error_filt_chips = 0.0;
    d_current_symbol = 0;
}


void galileo_e1_dll_pll_veml_tracking_cc::log_data()
{
    if (d_dump)
        {
            // Dump results to file
            float prompt_I;
            float prompt_Q;
            float tmp_VE, tmp_E, tmp_P, tmp_L, tmp_VL;
            float tmp_float;
            double tmp_double;

            prompt_I = static_cast<double>(d_P_accu.real());
            prompt_Q = static_cast<double>(d_P_accu.imag());

            tmp_VE = std::abs<float>(d_VE_accu);
            tmp_E = std::abs<float>(d_E_accu);
            tmp_P = std::abs<float>(d_P_accu);
            tmp_L = std::abs<float>(d_L_accu);
            tmp_VL = std::abs<float>(d_VL_accu);

            try
                {
                    // Dump correlators output
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_VE), sizeof(float));
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_E), sizeof(float));
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_P), sizeof(float));
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_L), sizeof(float));
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_VL), sizeof(float));
                    // PROMPT I and Q (to analyze navigation symbols)
                    d_dump_file.write(reinterpret_cast<char *>(&prompt_I), sizeof(float));
                    d_dump_file.write(reinterpret_cast<char *>(&prompt_Q), sizeof(float));
                    // PRN start sample stamp
                    d_dump_file.write(reinterpret_cast<char *>(&d_sample_counter), sizeof(unsigned long int));
                    // accumulated carrier phase
                    tmp_float = d_acc_carrier_phase_rad;
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_float), sizeof(float));
                    // carrier and code frequency
                    tmp_float = d_carrier_doppler_hz;
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_float), sizeof(float));
                    tmp_float = d_code_freq_chips;
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_float), sizeof(float));
                    // PLL commands
                    tmp_float = d_carr_error_hz;
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_float), sizeof(float));
                    tmp_float = d_carr_error_filt_hz;
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_float), sizeof(float));
                    // DLL commands
                    tmp_float = d_code_error_chips;
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_float), sizeof(float));
                    tmp_float = d_code_error_filt_chips;
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_float), sizeof(float));
                    // CN0 and carrier lock test
                    tmp_float = d_CN0_SNV_dB_Hz;
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_float), sizeof(float));
                    tmp_float = d_carrier_lock_test;
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_float), sizeof(float));
                    // AUX vars (for debug purposes)
                    tmp_float = d_rem_code_phase_samples;
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_float), sizeof(float));
                    tmp_double = static_cast<double>(d_sample_counter + d_current_prn_length_samples);
                    d_dump_file.write(reinterpret_cast<char *>(&tmp_double), sizeof(double));
                    // PRN
                    unsigned int prn_ = d_acquisition_gnss_synchro->PRN;
                    d_dump_file.write(reinterpret_cast<char *>(&prn_), sizeof(unsigned int));
                }
            catch (const std::ifstream::failure &e)
                {
                    LOG(WARNING) << "Exception writing trk dump file " << e.what();
                }
        }
}


int galileo_e1_dll_pll_veml_tracking_cc::general_work(int noutput_items __attribute__((unused)), gr_vector_int &ninput_items __attribute__((unused)),
    gr_vector_const_void_star &input_items, gr_vector_void_star &output_items)
{
    // Block input data and block output stream pointers
    const gr_complex *in = reinterpret_cast<const gr_complex *>(input_items[0]);
    Gnss_Synchro **out = reinterpret_cast<Gnss_Synchro **>(&output_items[0]);
    // GNSS_SYNCHRO OBJECT to interchange data between tracking->telemetry_decoder
    Gnss_Synchro current_synchro_data = Gnss_Synchro();

    switch (d_state)
        {
        case 0:  // standby - bypass
            {
                current_synchro_data.Tracking_sample_counter = d_sample_counter;
                break;
            }
        case 1:  // pull-in
            {
                /*
             * Signal alignment (skip samples until the incoming signal is aligned with local replica)
             */
                // Fill the acquisition data
                current_synchro_data = *d_acquisition_gnss_synchro;
                int samples_offset;
                double acq_trk_shif_correction_samples;
                int acq_to_trk_delay_samples;
                acq_to_trk_delay_samples = d_sample_counter - d_acq_sample_stamp;
                acq_trk_shif_correction_samples = d_current_prn_length_samples - std::fmod(static_cast<double>(acq_to_trk_delay_samples), static_cast<double>(d_current_prn_length_samples));
                samples_offset = round(d_acq_code_phase_samples + acq_trk_shif_correction_samples);
                current_synchro_data.Tracking_sample_counter = d_sample_counter;
                current_synchro_data.fs = d_fs_in;
                d_sample_counter = d_sample_counter + samples_offset;  // count for the processed samples
                consume_each(samples_offset);                          // shift input to perform alignment with local replica
                d_state = 2;                                           // next state is the symbol synchronization
                return 0;
            }
        case 2:  // wide tracking and symbol synchronization
            {
                // Fill the acquisition data
                current_synchro_data = *d_acquisition_gnss_synchro;
                // Current NCO and code generator parameters
                d_carrier_phase_step_rad = GALILEO_TWO_PI * d_carrier_doppler_hz / static_cast<double>(d_fs_in);
                d_code_phase_step_chips = d_code_freq_chips / static_cast<double>(d_fs_in);
                d_rem_code_phase_chips = d_rem_code_phase_samples * d_code_freq_chips / d_fs_in;
                // perform a correlation step
                do_correlation_step(in);
                // save single correlation step variables
                d_VE_accu = *d_Very_Early;
                d_E_accu = *d_Early;
                d_P_accu = *d_Prompt;
                d_L_accu = *d_Late;
                d_VL_accu = *d_Very_Late;
                // check lock status
                if (cn0_and_tracking_lock_status() == false)
                    {
                        clear_tracking_vars();
                        d_state = 0;  // loss-of-lock detected
                    }
                else
                    {
                        // perform DLL/PLL tracking loop computations
                        run_dll_pll(false);

                        // ################## PLL COMMANDS #################################################
                        // carrier phase accumulator for (K) Doppler estimation-
                        d_acc_carrier_phase_rad -= GALILEO_TWO_PI * d_carrier_doppler_hz * static_cast<double>(d_current_prn_length_samples) / static_cast<double>(d_fs_in);
                        // remnant carrier phase to prevent overflow in the code NCO
                        d_rem_carr_phase_rad = d_rem_carr_phase_rad + GALILEO_TWO_PI * d_carrier_doppler_hz * static_cast<double>(d_current_prn_length_samples) / static_cast<double>(d_fs_in);
                        d_rem_carr_phase_rad = std::fmod(d_rem_carr_phase_rad, GALILEO_TWO_PI);

                        // ################## DLL COMMANDS #################################################
                        // Code error from DLL
                        double code_error_filt_secs;
                        code_error_filt_secs = (Galileo_E1_CODE_PERIOD * d_code_error_filt_chips) / Galileo_E1_CODE_CHIP_RATE_HZ;  // [seconds]

                        // ################## CARRIER AND CODE NCO BUFFER ALIGNEMENT #######################
                        // keep alignment parameters for the next input buffer
                        // Compute the next buffer length based in the new period of the PRN sequence and the code phase error estimation
                        double T_chip_seconds = 1.0 / d_code_freq_chips;
                        double T_prn_seconds = T_chip_seconds * Galileo_E1_B_CODE_LENGTH_CHIPS;
                        double T_prn_samples = T_prn_seconds * static_cast<double>(d_fs_in);
                        double K_blk_samples = T_prn_samples + d_rem_code_phase_samples + code_error_filt_secs * static_cast<double>(d_fs_in);
                        d_current_prn_length_samples = round(K_blk_samples);  // round to a discrete number of samples

                        // ########### Output the tracking results to Telemetry block ##########
                        if (d_track_pilot)
                            {
                                current_synchro_data.Prompt_I = static_cast<double>((*d_Prompt_Data).real());
                                current_synchro_data.Prompt_Q = static_cast<double>((*d_Prompt_Data).imag());
                            }
                        else
                            {
                                current_synchro_data.Prompt_I = static_cast<double>((*d_Prompt).real());
                                current_synchro_data.Prompt_Q = static_cast<double>((*d_Prompt).imag());
                            }
                        current_synchro_data.Tracking_sample_counter = d_sample_counter;
                        current_synchro_data.Code_phase_samples = d_rem_code_phase_samples;
                        // compute remnant code phase samples AFTER the Tracking timestamp
                        d_rem_code_phase_samples = K_blk_samples - d_current_prn_length_samples;  // rounding error < 1 sample
                        current_synchro_data.Carrier_phase_rads = d_acc_carrier_phase_rad;
                        current_synchro_data.Carrier_Doppler_hz = d_carrier_doppler_hz;
                        current_synchro_data.CN0_dB_hz = d_CN0_SNV_dB_Hz;
                        current_synchro_data.Flag_valid_symbol_output = true;
                        current_synchro_data.correlation_length_ms = Galileo_E1_CODE_PERIOD_MS;

                        // enable write dump file this cycle (valid DLL/PLL cycle)
                        log_data();

                        //std::cout<<(d_Prompt->real()>0);
                        if (d_enable_extended_integration)
                            {
                                // ####### SECONDARY CODE LOCK #####
                                d_Prompt_buffer_deque.push_back(*d_Prompt);
                                if (d_Prompt_buffer_deque.size() == Galileo_E1_C_SECONDARY_CODE_LENGTH)
                                    {
                                        if (acquire_secondary() == true)
                                            {
                                                d_extend_correlation_symbols_count = 0;
                                                // reset extended correlator
                                                d_VE_accu = gr_complex(0, 0);
                                                d_E_accu = gr_complex(0, 0);
                                                d_P_accu = gr_complex(0, 0);
                                                d_L_accu = gr_complex(0, 0);
                                                d_VL_accu = gr_complex(0, 0);
                                                d_Prompt_buffer_deque.clear();
                                                d_current_symbol = 0;
                                                d_code_loop_filter.set_DLL_BW(d_dll_bw_narrow_hz);
                                                d_carrier_loop_filter.set_PLL_BW(d_pll_bw_narrow_hz);

                                                // Set TAPs delay values [chips]
                                                d_local_code_shift_chips[0] = -d_very_early_late_spc_narrow_chips;
                                                d_local_code_shift_chips[1] = -d_early_late_spc_narrow_chips;
                                                d_local_code_shift_chips[2] = 0.0;
                                                d_local_code_shift_chips[3] = d_early_late_spc_narrow_chips;
                                                d_local_code_shift_chips[4] = d_very_early_late_spc_narrow_chips;

                                                LOG(INFO) << "Enabled " << d_extend_correlation_symbols << " [symbols] extended correlator for CH "
                                                          << d_channel
                                                          << " : Satellite " << Gnss_Satellite(systemName[sys], d_acquisition_gnss_synchro->PRN);
                                                std::cout << "Enabled " << d_extend_correlation_symbols << " [symbols] extended correlator for CH "
                                                          << d_channel
                                                          << " : Satellite " << Gnss_Satellite(systemName[sys], d_acquisition_gnss_synchro->PRN) << std::endl;
                                                //std::cout << " pll_bw = " << d_pll_bw_hz << " [Hz], pll_narrow_bw = " << d_pll_bw_narrow_hz << " [Hz]" << std::endl;
                                                //std::cout << " dll_bw = " << d_dll_bw_hz << " [Hz], dll_narrow_bw = " << d_dll_bw_narrow_hz << " [Hz]" << std::endl;

                                                // UPDATE INTEGRATION TIME
                                                double new_correlation_time_s = static_cast<double>(d_extend_correlation_symbols) * Galileo_E1_CODE_PERIOD;
                                                d_carrier_loop_filter.set_pdi(new_correlation_time_s);
                                                d_code_loop_filter.set_pdi(new_correlation_time_s);

                                                d_state = 3;  // next state is the extended correlator integrator
                                            }

                                        d_Prompt_buffer_deque.pop_front();
                                    }
                            }
                    }
                break;
            }
        case 3:  // coherent integration (correlation time extension)
            {
                // Fill the acquisition data
                current_synchro_data = *d_acquisition_gnss_synchro;
                // Current NCO and code generator parameters
                d_carrier_phase_step_rad = GALILEO_TWO_PI * d_carrier_doppler_hz / static_cast<double>(d_fs_in);
                d_code_phase_step_chips = d_code_freq_chips / static_cast<double>(d_fs_in);
                d_rem_code_phase_chips = d_rem_code_phase_samples * d_code_freq_chips / d_fs_in;
                // perform a correlation step
                do_correlation_step(in);
                // correct the integration sign using the current symbol of the secondary code
                if (Galileo_E1_C_SECONDARY_CODE.at(d_current_symbol) == '0')
                    {
                        d_VE_accu += *d_Very_Early;
                        d_E_accu += *d_Early;
                        d_P_accu += *d_Prompt;
                        d_L_accu += *d_Late;
                        d_VL_accu += *d_Very_Late;
                    }
                else
                    {
                        d_VE_accu -= *d_Very_Early;
                        d_E_accu -= *d_Early;
                        d_P_accu -= *d_Prompt;
                        d_L_accu -= *d_Late;
                        d_VL_accu -= *d_Very_Late;
                    }
                d_current_symbol++;
                // secondary code roll-up
                d_current_symbol = d_current_symbol % Galileo_E1_C_SECONDARY_CODE_LENGTH;

                // PLL/DLL not enabled, we are in the middle of a coherent integration
                // keep alignment parameters for the next input buffer
                // Compute the next buffer length based in the new period of the PRN sequence and the code phase error estimation

                // ################## PLL ##########################################################
                // carrier phase accumulator for (K) Doppler estimation-
                d_acc_carrier_phase_rad -= GALILEO_TWO_PI * d_carrier_doppler_hz * static_cast<double>(d_current_prn_length_samples) / static_cast<double>(d_fs_in);
                // remnant carrier phase to prevent overflow in the code NCO
                d_rem_carr_phase_rad = d_rem_carr_phase_rad + GALILEO_TWO_PI * d_carrier_doppler_hz * static_cast<double>(d_current_prn_length_samples) / static_cast<double>(d_fs_in);
                d_rem_carr_phase_rad = std::fmod(d_rem_carr_phase_rad, GALILEO_TWO_PI);

                // ################## CARRIER AND CODE NCO BUFFER ALIGNEMENT #######################
                // keep alignment parameters for the next input buffer
                // Compute the next buffer length based in the new period of the PRN sequence and the code phase error estimation
                double T_chip_seconds = 1.0 / d_code_freq_chips;
                double T_prn_seconds = T_chip_seconds * Galileo_E1_B_CODE_LENGTH_CHIPS;
                double T_prn_samples = T_prn_seconds * static_cast<double>(d_fs_in);
                double K_blk_samples = T_prn_samples + d_rem_code_phase_samples;
                d_current_prn_length_samples = round(K_blk_samples);  //round to a discrete samples

                // ########### Output the tracking results to Telemetry block ##########
                current_synchro_data.Prompt_I = static_cast<double>((*d_Prompt_Data).real());
                current_synchro_data.Prompt_Q = static_cast<double>((*d_Prompt_Data).imag());
                current_synchro_data.Tracking_sample_counter = d_sample_counter;
                current_synchro_data.Code_phase_samples = d_rem_code_phase_samples;
                // compute remnant code phase samples AFTER the Tracking timestamp
                d_rem_code_phase_samples = K_blk_samples - d_current_prn_length_samples;  //rounding error < 1 sample
                current_synchro_data.Carrier_phase_rads = d_acc_carrier_phase_rad;
                current_synchro_data.Carrier_Doppler_hz = d_carrier_doppler_hz;
                current_synchro_data.CN0_dB_hz = d_CN0_SNV_dB_Hz;
                current_synchro_data.Flag_valid_symbol_output = true;
                current_synchro_data.correlation_length_ms = Galileo_E1_CODE_PERIOD_MS;

                d_extend_correlation_symbols_count++;
                if (d_extend_correlation_symbols_count >= (d_extend_correlation_symbols - 1))
                    {
                        d_extend_correlation_symbols_count = 0;
                        d_state = 4;
                    }
                break;
            }
        case 4:  // narrow tracking
            {
                // Fill the acquisition data
                current_synchro_data = *d_acquisition_gnss_synchro;
                // perform a correlation step
                do_correlation_step(in);

                // correct the integration using the current symbol
                if (Galileo_E1_C_SECONDARY_CODE.at(d_current_symbol) == '0')
                    {
                        d_VE_accu += *d_Very_Early;
                        d_E_accu += *d_Early;
                        d_P_accu += *d_Prompt;
                        d_L_accu += *d_Late;
                        d_VL_accu += *d_Very_Late;
                    }
                else
                    {
                        d_VE_accu -= *d_Very_Early;
                        d_E_accu -= *d_Early;
                        d_P_accu -= *d_Prompt;
                        d_L_accu -= *d_Late;
                        d_VL_accu -= *d_Very_Late;
                    }
                d_current_symbol++;
                // secondary code roll-up
                d_current_symbol = d_current_symbol % Galileo_E1_C_SECONDARY_CODE_LENGTH;

                // check lock status
                if (cn0_and_tracking_lock_status() == false)
                    {
                        clear_tracking_vars();
                        d_state = 0;  // loss-of-lock detected
                    }
                else
                    {
                        run_dll_pll(true);  // Costas loop disabled, use four quadrant atan

                        // ################## PLL ##########################################################
                        // carrier phase accumulator for (K) Doppler estimation-
                        d_acc_carrier_phase_rad -= GALILEO_TWO_PI * d_carrier_doppler_hz * static_cast<double>(d_current_prn_length_samples) / static_cast<double>(d_fs_in);
                        // remnant carrier phase to prevent overflow in the code NCO
                        d_rem_carr_phase_rad = d_rem_carr_phase_rad + GALILEO_TWO_PI * d_carrier_doppler_hz * static_cast<double>(d_current_prn_length_samples) / static_cast<double>(d_fs_in);
                        d_rem_carr_phase_rad = std::fmod(d_rem_carr_phase_rad, GALILEO_TWO_PI);

                        // ################## DLL ##########################################################
                        // Code phase accumulator
                        double code_error_filt_secs;
                        code_error_filt_secs = (Galileo_E1_CODE_PERIOD * d_code_error_filt_chips) / Galileo_E1_CODE_CHIP_RATE_HZ;  //[seconds]

                        // ################## CARRIER AND CODE NCO BUFFER ALIGNEMENT #######################
                        // keep alignment parameters for the next input buffer
                        // Compute the next buffer length based in the new period of the PRN sequence and the code phase error estimation
                        double T_chip_seconds = 1.0 / d_code_freq_chips;
                        double T_prn_seconds = T_chip_seconds * Galileo_E1_B_CODE_LENGTH_CHIPS;
                        double T_prn_samples = T_prn_seconds * static_cast<double>(d_fs_in);
                        double K_blk_samples = T_prn_samples + d_rem_code_phase_samples + code_error_filt_secs * static_cast<double>(d_fs_in);
                        d_current_prn_length_samples = round(K_blk_samples);  // round to a discrete number of samples

                        // ########### Output the tracking results to Telemetry block ##########
                        current_synchro_data.Prompt_I = static_cast<double>((*d_Prompt_Data).real());
                        current_synchro_data.Prompt_Q = static_cast<double>((*d_Prompt_Data).imag());
                        current_synchro_data.Tracking_sample_counter = d_sample_counter;
                        current_synchro_data.Code_phase_samples = d_rem_code_phase_samples;
                        // compute remnant code phase samples AFTER the Tracking timestamp
                        d_rem_code_phase_samples = K_blk_samples - d_current_prn_length_samples;  //rounding error < 1 sample
                        current_synchro_data.Carrier_phase_rads = d_acc_carrier_phase_rad;
                        current_synchro_data.Carrier_Doppler_hz = d_carrier_doppler_hz;
                        current_synchro_data.CN0_dB_hz = d_CN0_SNV_dB_Hz;
                        current_synchro_data.Flag_valid_symbol_output = true;
                        current_synchro_data.correlation_length_ms = Galileo_E1_CODE_PERIOD_MS;
                        // enable write dump file this cycle (valid DLL/PLL cycle)
                        log_data();
                        // reset extended correlator
                        d_VE_accu = gr_complex(0, 0);
                        d_E_accu = gr_complex(0, 0);
                        d_P_accu = gr_complex(0, 0);
                        d_L_accu = gr_complex(0, 0);
                        d_VL_accu = gr_complex(0, 0);
                        d_state = 3;  //new coherent integration (correlation time extension) cycle
                    }
            }
        }

    //assign the GNURadio block output data
    //    current_synchro_data.System = {'E'};
    //    std::string str_aux = "1B";
    //    const char * str = str_aux.c_str(); // get a C style null terminated string
    //    std::memcpy(static_cast<void*>(current_synchro_data.Signal), str, 3);

    current_synchro_data.fs = d_fs_in;
    *out[0] = current_synchro_data;

    consume_each(d_current_prn_length_samples);        // this is required for gr_block derivates
    d_sample_counter += d_current_prn_length_samples;  // count for the processed samples

    if (current_synchro_data.Flag_valid_symbol_output)
        {
            return 1;
        }
    else
        {
            return 0;
        }
}


int galileo_e1_dll_pll_veml_tracking_cc::save_matfile()
{
    // READ DUMP FILE
    std::ifstream::pos_type size;
    int number_of_double_vars = 1;
    int number_of_float_vars = 17;
    int epoch_size_bytes = sizeof(unsigned long int) + sizeof(double) * number_of_double_vars +
                           sizeof(float) * number_of_float_vars + sizeof(unsigned int);
    std::ifstream dump_file;
    dump_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
        {
            dump_file.open(d_dump_filename.c_str(), std::ios::binary | std::ios::ate);
        }
    catch (const std::ifstream::failure &e)
        {
            std::cerr << "Problem opening dump file:" << e.what() << std::endl;
            return 1;
        }
    // count number of epochs and rewind
    long int num_epoch = 0;
    if (dump_file.is_open())
        {
            size = dump_file.tellg();
            num_epoch = static_cast<long int>(size) / static_cast<long int>(epoch_size_bytes);
            dump_file.seekg(0, std::ios::beg);
        }
    else
        {
            return 1;
        }
    float *abs_VE = new float[num_epoch];
    float *abs_E = new float[num_epoch];
    float *abs_P = new float[num_epoch];
    float *abs_L = new float[num_epoch];
    float *abs_VL = new float[num_epoch];
    float *Prompt_I = new float[num_epoch];
    float *Prompt_Q = new float[num_epoch];
    unsigned long int *PRN_start_sample_count = new unsigned long int[num_epoch];
    float *acc_carrier_phase_rad = new float[num_epoch];
    float *carrier_doppler_hz = new float[num_epoch];
    float *code_freq_chips = new float[num_epoch];
    float *carr_error_hz = new float[num_epoch];
    float *carr_error_filt_hz = new float[num_epoch];
    float *code_error_chips = new float[num_epoch];
    float *code_error_filt_chips = new float[num_epoch];
    float *CN0_SNV_dB_Hz = new float[num_epoch];
    float *carrier_lock_test = new float[num_epoch];
    float *aux1 = new float[num_epoch];
    double *aux2 = new double[num_epoch];
    unsigned int *PRN = new unsigned int[num_epoch];

    try
        {
            if (dump_file.is_open())
                {
                    for (long int i = 0; i < num_epoch; i++)
                        {
                            dump_file.read(reinterpret_cast<char *>(&abs_VE[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&abs_E[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&abs_P[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&abs_L[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&abs_VL[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&Prompt_I[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&Prompt_Q[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&PRN_start_sample_count[i]), sizeof(unsigned long int));
                            dump_file.read(reinterpret_cast<char *>(&acc_carrier_phase_rad[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&carrier_doppler_hz[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&code_freq_chips[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&carr_error_hz[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&carr_error_filt_hz[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&code_error_chips[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&code_error_filt_chips[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&CN0_SNV_dB_Hz[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&carrier_lock_test[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&aux1[i]), sizeof(float));
                            dump_file.read(reinterpret_cast<char *>(&aux2[i]), sizeof(double));
                            dump_file.read(reinterpret_cast<char *>(&PRN[i]), sizeof(unsigned int));
                        }
                }
            dump_file.close();
        }
    catch (const std::ifstream::failure &e)
        {
            std::cerr << "Problem reading dump file:" << e.what() << std::endl;
            delete[] abs_VE;
            delete[] abs_E;
            delete[] abs_P;
            delete[] abs_L;
            delete[] abs_VL;
            delete[] Prompt_I;
            delete[] Prompt_Q;
            delete[] PRN_start_sample_count;
            delete[] acc_carrier_phase_rad;
            delete[] carrier_doppler_hz;
            delete[] code_freq_chips;
            delete[] carr_error_hz;
            delete[] carr_error_filt_hz;
            delete[] code_error_chips;
            delete[] code_error_filt_chips;
            delete[] CN0_SNV_dB_Hz;
            delete[] carrier_lock_test;
            delete[] aux1;
            delete[] aux2;
            delete[] PRN;
            return 1;
        }

    // WRITE MAT FILE
    mat_t *matfp;
    matvar_t *matvar;
    std::string filename = d_dump_filename;
    filename.erase(filename.length() - 4, 4);
    filename.append(".mat");
    matfp = Mat_CreateVer(filename.c_str(), NULL, MAT_FT_MAT73);
    if (reinterpret_cast<long *>(matfp) != NULL)
        {
            size_t dims[2] = {1, static_cast<size_t>(num_epoch)};
            matvar = Mat_VarCreate("abs_VE", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, abs_E, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("abs_E", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, abs_E, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("abs_P", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, abs_P, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("abs_L", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, abs_L, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("abs_VL", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, abs_E, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("Prompt_I", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, Prompt_I, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("Prompt_Q", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, Prompt_Q, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("PRN_start_sample_count", MAT_C_UINT64, MAT_T_UINT64, 2, dims, PRN_start_sample_count, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("acc_carrier_phase_rad", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, acc_carrier_phase_rad, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("carrier_doppler_hz", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, carrier_doppler_hz, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("code_freq_chips", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, code_freq_chips, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("carr_error_hz", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, carr_error_hz, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("carr_error_filt_hz", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, carr_error_filt_hz, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("code_error_chips", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, code_error_chips, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("code_error_filt_chips", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, code_error_filt_chips, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("CN0_SNV_dB_Hz", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, CN0_SNV_dB_Hz, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("carrier_lock_test", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, carrier_lock_test, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("aux1", MAT_C_SINGLE, MAT_T_SINGLE, 2, dims, aux1, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("aux2", MAT_C_DOUBLE, MAT_T_DOUBLE, 2, dims, aux2, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);

            matvar = Mat_VarCreate("PRN", MAT_C_UINT32, MAT_T_UINT32, 2, dims, PRN, 0);
            Mat_VarWrite(matfp, matvar, MAT_COMPRESSION_ZLIB);  // or MAT_COMPRESSION_NONE
            Mat_VarFree(matvar);
        }
    Mat_Close(matfp);
    delete[] abs_VE;
    delete[] abs_E;
    delete[] abs_P;
    delete[] abs_L;
    delete[] abs_VL;
    delete[] Prompt_I;
    delete[] Prompt_Q;
    delete[] PRN_start_sample_count;
    delete[] acc_carrier_phase_rad;
    delete[] carrier_doppler_hz;
    delete[] code_freq_chips;
    delete[] carr_error_hz;
    delete[] carr_error_filt_hz;
    delete[] code_error_chips;
    delete[] code_error_filt_chips;
    delete[] CN0_SNV_dB_Hz;
    delete[] carrier_lock_test;
    delete[] aux1;
    delete[] aux2;
    delete[] PRN;
    return 0;
}


void galileo_e1_dll_pll_veml_tracking_cc::set_channel(unsigned int channel)
{
    d_channel = channel;
    LOG(INFO) << "Tracking Channel set to " << d_channel;
    // ############# ENABLE DATA FILE LOG #################
    if (d_dump == true)
        {
            if (d_dump_file.is_open() == false)
                {
                    try
                        {
                            d_dump_filename.append(boost::lexical_cast<std::string>(d_channel));
                            d_dump_filename.append(".dat");
                            d_dump_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
                            d_dump_file.open(d_dump_filename.c_str(), std::ios::out | std::ios::binary);
                            LOG(INFO) << "Tracking dump enabled on channel " << d_channel << " Log file: " << d_dump_filename.c_str();
                        }
                    catch (const std::ifstream::failure &e)
                        {
                            LOG(WARNING) << "channel " << d_channel << " Exception opening trk dump file " << e.what();
                        }
                }
        }
}


void galileo_e1_dll_pll_veml_tracking_cc::set_gnss_synchro(Gnss_Synchro *p_gnss_synchro)
{
    d_acquisition_gnss_synchro = p_gnss_synchro;
}
