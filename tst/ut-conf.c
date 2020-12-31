/*******************************************************************************
Not Another Configuration System
Copyright (C) 2020, Antonis Kalamaras (kalamara AT ceid DOT upatras DOT gr)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"

#include "config.h"
#include "schema.h"

#include "ut-conf.h"

#define TRUE 1
#define FALSE 0

int init_suite_success (void)
{
  return 0;
}
int init_suite_failure (void)
{
  return -1;
}
int clean_suite_success (void)
{
  return 0;
}
int clean_suite_failure (void)
{
  return -1;
}

#define ADD_TEST(suite,name)\
  (NULL == CU_add_test((suite),#name,name))


int main ()
{
  CU_pSuite           suite_conf = NULL;
  
  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry ())
    return CU_get_error ();

  /* add a suite to the registry */
  
  suite_conf = CU_add_suite ("configurator library core", 
                           init_suite_success,
                           clean_suite_success);
  
    
  if(NULL == suite_conf) 
  {
    CU_cleanup_registry ();
    return CU_get_error ();
  }

 // start_thread();
  
  //configurator
  if(ADD_TEST(suite_conf, ut_conf) 
  || ADD_TEST(suite_conf, ut_store)
  || ADD_TEST(suite_conf, ut_get)
  || ADD_TEST(suite_conf, ut_set)
  || ADD_TEST(suite_conf, ut_copy)
  ){
	CU_cleanup_registry ();
        return CU_get_error ();
  }

  /* Run all tests using the basic interface */

  CU_basic_set_mode (CU_BRM_VERBOSE);
  CU_basic_run_tests ();
  printf ("\n");
  CU_basic_show_failures (CU_get_failure_list ());
  printf ("\n\n");

  /* Run all tests using the automated interface */
  /*CU_automated_enable_junit_xml(0);*/
  CU_automated_run_tests ();
  CU_list_tests_to_file ();

  /* Clean up registry and return */
  CU_cleanup_registry ();

  //stop_thread();

  return CU_get_error ();
}

