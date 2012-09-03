/*!
 * \file kml_printer.h
 * \brief Implementation of a NMEA 2.1 printer for GNSS-SDR
 * This class provides a implementation of a subset of the NMEA-0183 standard for interfacing
 * marine electronic devices as defined by the National Marine Electronics Association (NMEA).
 * See http://www.nmea.org/ for the NMEA 183 standard
 *
 * \author Javier Arribas, 2012. jarribas(at)cttc.es
 *
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2012  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
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

#ifndef GNSS_SDR_NMEA_PRINTER_H_
#define	 GNSS_SDR_NMEA_PRINTER_H_


#include <iostream>
#include <fstream>
#include "gps_l1_ca_ls_pvt.h"

class Nmea_Printer
{
public:
    /*!
     * \brief Default constructor.
     */
    Nmea_Printer(std::string filename, bool flag_nmea_tty_port, std::string nmea_dump_filename);

    /*!
     * \brief Print NMEA PVT and satellite info to the initialized device
     */
    bool Print_Nmea_Line(gps_l1_ca_ls_pvt* position, bool print_average_values);

    /*!
     * \brief Default destructor.
     */
    ~Nmea_Printer();


private:
    std::string nmea_filename ; //<! String with the NMEA log filename
    std::ofstream nmea_file_descriptor ; //<! Output file stream for NMEA log file
    std::string nmea_devname;
    int nmea_dev_descriptor ; //<! NMEA serial device descriptor (i.e. COM port)

    gps_l1_ca_ls_pvt* d_PVT_data;

    int init_serial (std::string serial_device); //serial port control
    void close_serial ();

    std::string get_GPGGA();
    std::string get_GPGSV();
    std::string get_GPGSA();
    std::string get_GPRMC();
    std::string get_UTC_NMEA_time(boost::posix_time::ptime d_position_UTC_time);
    std::string longitude_to_hm(double longitude);
    std::string latitude_to_hm(double lat);
    char checkSum(std::string sentence);

};

#endif