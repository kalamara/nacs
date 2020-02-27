#ifndef _UT_YML_H_ 
#define _UT_YML_H_

extern struct entry ConfigSchema[];
extern struct entry HwSchema[];
extern struct entry SimSchema[];
extern struct entry SubdevSchema[];
extern struct entry ComediSchema[];

void ut_load()
{
    
    config_t def = init_config(ConfigSchema, N_CONFIG_VARIABLES);
    
    config_t conf = deserialize_config(NULL, def);

    CU_ASSERT(conf->err == CONF_ERR);
    conf->err = CONF_OK;
   
    conf = deserialize_config("STEP: 100", def);
    CU_ASSERT(conf->err == CONF_OK);
    
    entry_t got = get_entry(CONFIG_STEP, def);
    CU_ASSERT(got->e.scalar_int == 100);
    
    char * input = "\n\
AI:  \n\
 - 5 \n\
 - INDEX  :     1    \n\
   ID     :    var1\n\
   VALUE  :    5.0\n\
   MIN    :    0.0\n\
   MAX    :   24.0\n";
 
    conf = deserialize_config(input, def);
    CU_ASSERT(conf->err == CONF_OK);
    
    got = get_entry(CONFIG_AI,conf);
    CU_ASSERT(got->type_tag == ENTRY_SEQ);
    CU_ASSERT(got->e.seq->size == 5);
    char * max = get_param_val("MAX",
        got->e.seq->vars[1].params);
    CU_ASSERT_STRING_EQUAL(max, "24.0");
    
    config_t sim = init_config(SimSchema, N_SIM_VARS);
    input = 
"#SIMULATION IO \n\
INPUT:   simin.txt \n\
OUTPUT:  simout.txt \n\
";
    conf = deserialize_config(input, sim);
    CU_ASSERT(conf->err == CONF_OK);
   
    got = get_entry(
            SIM_INPUT, 
            conf);
    
    CU_ASSERT(got->type_tag == ENTRY_STR);
    CU_ASSERT_STRING_EQUAL(got->name, "INPUT");
    CU_ASSERT_STRING_EQUAL(got->e.scalar_str, "simin.txt");
    //printf("%s\n", got->e.scalar_str);

    input = 
"#COMEDI interface:\n\
    FILE:     1 \n\
    SUBDEV :     \n\
        IN :  5 \n\
        OUT:  6 \n\
        ADC:  7 \n\
        DAC:  8 \n\
";  

    config_t subdev = init_config(SubdevSchema, N_SUBDEV_VARS);
    ComediSchema[COMEDI_SUBDEV].e.conf = subdev;
    
    config_t comedi = init_config(ComediSchema, N_COMEDI_VARS);
    

    conf = deserialize_config(input, comedi);
    CU_ASSERT(conf->err == CONF_OK);
   
    got = get_entry(
            SUBDEV_IN, 
            get_entry(
                COMEDI_SUBDEV,
                conf)->e.conf);
    
    CU_ASSERT_EQUAL(got->e.scalar_int, 5);

    clear_config(subdev); 
    clear_config(comedi); 
    clear_config(sim);    
    clear_config(def);
}

void ut_save(){
    config_t conf = init_config(ConfigSchema, N_CONFIG_VARIABLES);
    sequence_t seq = conf->map[CONFIG_AI]->e.seq;
    conf = store_seq_value(seq, 0, "MAX", "1.0", conf);
    conf = store_seq_value(seq, 0, "ID", "var1", conf);

    char * output = serialize_config( conf);    
    char * expected = "\
---\n\
STEP: 100\n\
HW: !!map {}\n\
PROGRAM:\n\
- 2\n\
AI:\n\
- 2\n\
- INDEX: 0\n\
  ID: var1\n\
  MAX: 1.0\n\
AQ:\n\
- 2\n\
DI:\n\
- 2\n\
DQ:\n\
- 2\n\
MVAR:\n\
- 2\n\
MREG:\n\
- 2\n\
TIMERS:\n\
- 2\n\
PULSES:\n\
- 2\n\
...\n\
";
    
	CU_ASSERT_STRING_EQUAL(output,expected);
	//printf("%s\n", output);
	clear_config(conf);
	free(output);
}

#endif//_UT_YML_H_
