
/*
 * 
 * Simulation_Run of A Single Server Queueing System
 * 
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA,
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/******************************************************************************/

#include <stdio.h>
#include "simparameters.h"
#include "main.h"
#include "output.h"

/******************************************************************************/

/*
 * This function outputs a progress message to the screen to indicate this are
 * working.
 */

void
output_progress_msg_to_screen(Simulation_Run_Ptr simulation_run)
{
  double percentage_done;
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  data->blip_counter++;

  if((data->blip_counter >= BLIPRATE)
     ||
     (data->number_of_packets_processed >= RUNLENGTH)) {

    data->blip_counter = 0;

    percentage_done =
      100 * (double) data->number_of_packets_processed/RUNLENGTH;

    printf("%3.0f%% ", percentage_done);

    printf("Successfully Xmtted Pkts  = %ld (Arrived Pkts = %ld) \r", 
	   data->number_of_packets_processed, data->arrival_count);

    fflush(stdout);
  }

}

/*
 * When a simulation_run run is completed, this function outputs various
 * collected statistics on the screen.
 */

void
output_results(Simulation_Run_Ptr simulation_run)
{
  double xmtted_fraction;
  Simulation_Run_Data_Ptr data;
  double mean_delay, delay_rate;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  FILE *f;
  f = fopen("./outputs/output_part3.csv", "a");
  // fprintf(f, "Random Number Seed, Packet arrival count, Transmitted packet count, Arrival Rate, Mean delay\n");

  printf("\n");
  printf("Random Seed = %d \n", data->random_seed);
  printf("Packet arrival count = %ld \n", data->arrival_count);

  xmtted_fraction = (double) data->number_of_packets_processed /
    data->arrival_count;

  printf("Transmitted packet count  = %ld (Service Fraction = %.5f)\n",
	 data->number_of_packets_processed, xmtted_fraction);

  printf("Arrival rate = %.3f packets/second \n", (double) PACKET_ARRIVAL_RATE);

  mean_delay = 1e3*data->accumulated_delay/data->number_of_packets_processed;
  printf("Mean Delay (msec) = %f \n", mean_delay);

  delay_rate = data->delay_count/data->number_of_packets_processed;
  printf("Delay Rate = %f \n", delay_rate);

  fprintf(f, "%d, %ld, %f, %f, %f\n", data->random_seed, data->number_of_packets_processed, (double) PACKET_ARRIVAL_RATE, 1e3*data->accumulated_delay/data->number_of_packets_processed, delay_rate);
  fclose(f);
  printf("\n");
}



