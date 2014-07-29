define(`_FILE_', `propertyInitPid2')
include(code.m4)

define(`_TIME_', `Discrete')

code(system,ParkingSystem)

code(type,range,RTDS_character,integer,32,127)
code(type,string,RTDS_charstring,RTDS_character,128)
code(type,range,i_spots,integer,0,2)
code(type,record,InfoZone,(totalSpots,i_spots,freeSpots,i_spots,ID,pid))
code(type,record,t_sEntered_Car,(p1,pid,p2,InfoZone))
code(type,record,t_sOut_Car,(p1,pid,p2,InfoZone))
code(type,record,t_sOkInit,(p1,pid,p2,InfoZone))
code(type,record,t_sInfoZone,(p1,pid,p2,InfoZone))
code(type,record,t_sInitFreeSpot,(p1,pid,p2,i_spots))
code(type,record,t_sInitTotalSpots,(p1,pid,p2,i_spots))
code(type,record,t_sReqInfo,(p1,pid))
code(type,record,t_sLoopInductive_Zone,(p1,pid))
code(type,record,t_sIR1_Zone,(p1,pid))
code(type,record,t_sIR2_Zone,(p1,pid))
code(type,record,t_sIR3_Zone,(p1,pid))
code(type,record,t_sIR4_Zone,(p1,pid))
code(type,record,t_sTemp,(p1,pid))
code(type,record,t_sOkInitPid,(p1,pid))
code(type,record,t_sInitPidCtrl,(p1,pid,p2,pid))
code(type,sig_union,t_if_signal,(sEntered_Car,t_sEntered_Car,sOut_Car,t_sOut_Car,sOkInit,t_sOkInit,sInfoZone,t_sInfoZone,sInitFreeSpot,t_sInitFreeSpot,sInitTotalSpots,t_sInitTotalSpots,sReqInfo,t_sReqInfo,sLoopInductive_Zone,t_sLoopInductive_Zone,sIR1_Zone,t_sIR1_Zone,sIR2_Zone,t_sIR2_Zone,sIR3_Zone,t_sIR3_Zone,sIR4_Zone,t_sIR4_Zone,sTemp,t_sTemp,sOkInitPid,t_sOkInitPid,sInitPidCtrl,t_sInitPidCtrl))

code(message,sEntered_Car,0,
	(p1,pid,p2,InfoZone))
code(message,sOut_Car,1,
	(p1,pid,p2,InfoZone))
code(message,sOkInit,2,
	(p1,pid,p2,InfoZone))
code(message,sInfoZone,3,
	(p1,pid,p2,InfoZone))
code(message,sInitFreeSpot,4,
	(p1,pid,p2,i_spots))
code(message,sInitTotalSpots,5,
	(p1,pid,p2,i_spots))
code(message,sReqInfo,6,
	(p1,pid))
code(message,sLoopInductive_Zone,7,
	(p1,pid))
code(message,sIR1_Zone,8,
	(p1,pid))
code(message,sIR2_Zone,9,
	(p1,pid))
code(message,sIR3_Zone,10,
	(p1,pid))
code(message,sIR4_Zone,11,
	(p1,pid))
code(message,sTemp,12,
	(p1,pid))
code(message,sOkInitPid,13,
	(p1,pid))
code(message,sInitPidCtrl,14,
	(p1,pid,p2,pid))











code(system_instance, ParkingSystem)
code(end_system_instance)

code(instance,pZone,10,
	(PARENT,pid),
	(OFFSPRING,pid,SENDER,pid,RTDS_skip,boolean,RTDS_stop,boolean,p_freeSpots,i_spots,p_totalSpots,i_spots,TmpfreeSpots,i_spots,TmptotalSpots,i_spots,freeSpots,i_spots,totalSpots,i_spots,PidZone,pid,pid_Ctrl,pid,pidCtrl,pid,infoTableZone,InfoZone),
	(),
	(top,integer),(top,-1,top,1,),
	(sIR1_Zone,sInitTotalSpots,sIR2_Zone,sInitPidCtrl,sLoopInductive_Zone,sReqInfo,sIR4_Zone,sIR3_Zone,sInitFreeSpot))

code(dispatch,top,)

code(dispatch,RTDS_START,top,
	(,1))

code(fire,RTDS_START,1,EAGER,,if_boolean_true,({0,0,0}),
	,((a),(b),(c),(d),(e)),f,,,141)
code(action,RTDS_START,1,a,
	task,pid,m_var.PidZone,m_pid)
code(action,RTDS_START,1,b,
	task,pid,m_var.infoTableZone.ID,m_var.PidZone)
code(action,RTDS_START,1,c,
	task,i_spots,m_var.infoTableZone.freeSpots,2)
code(action,RTDS_START,1,d,
	task,i_spots,m_var.infoTableZone.totalSpots,2)
code(action,RTDS_START,1,e,
	output,sTemp,(m_pid),0,0)
code(action,RTDS_START,1,f,
	nextstate,(top,-1,top,3,))


code(dispatch,sWait,top,
	(,1))

code(fire,sWait,1,EAGER,,if_boolean_true,({0,0,0}),
	,((a)),b,,,152)
code(action,sWait,1,a,
	output,sOkInitPid,(m_pid),0,0)
code(action,sWait,1,b,
	nextstate,(top,-1,top,2,))


code(dispatch,Idle,top,
	(sReqInfo,1),
	(sIR1_Zone,2),
	(sInitPidCtrl,3),
	(sInitFreeSpot,4),
	(sIR3_Zone,5),
	(sInitTotalSpots,6))

code(fire,Idle,1,DELAYABLE,,,({0,0,0}),
	a,((b)),c,,,161)
code(action,Idle,1,a,
	input,sReqInfo,(m_var.SENDER,p1,pid))
code(action,Idle,1,b,
	output,sInfoZone,(m_pid,m_var.infoTableZone),0,0)
code(action,Idle,1,c,
	nextstate,(top,-1,top,3,))

code(fire,Idle,2,DELAYABLE,,,({0,0,0}),
	a,(),b,,,166)
code(action,Idle,2,a,
	input,sIR1_Zone,(m_var.SENDER,p1,pid))

code(action,Idle,2,b,
	nextstate,(top,-1,top,5,))

code(fire,Idle,3,DELAYABLE,,,({0,0,0}),
	a,((b)),c,,,170)
code(action,Idle,3,a,
	input,sInitPidCtrl,(m_var.SENDER,p1,pid,m_var.pidCtrl,p2,pid))
code(action,Idle,3,b,
	task,pid,m_var.pid_Ctrl,m_var.pidCtrl)
code(action,Idle,3,c,
	nextstate,(top,-1,top,2,))

code(fire,Idle,4,DELAYABLE,,,({0,0,0}),
	a,((b),(c)),d,,,175)
code(action,Idle,4,a,
	input,sInitFreeSpot,(m_var.SENDER,p1,pid,m_var.p_freeSpots,p2,i_spots))
code(action,Idle,4,b,
	task,i_spots,m_var.infoTableZone.freeSpots,m_var.p_freeSpots)
code(action,Idle,4,c,
	output,sOkInit,(m_pid,m_var.infoTableZone),0,0)
code(action,Idle,4,d,
	nextstate,(top,-1,top,3,))

code(fire,Idle,5,DELAYABLE,,,({0,0,0}),
	a,(),b,,,181)
code(action,Idle,5,a,
	input,sIR3_Zone,(m_var.SENDER,p1,pid))

code(action,Idle,5,b,
	nextstate,(top,-1,top,4,))

code(fire,Idle,6,DELAYABLE,,,({0,0,0}),
	a,((b),(c)),d,,,185)
code(action,Idle,6,a,
	input,sInitTotalSpots,(m_var.SENDER,p1,pid,m_var.p_totalSpots,p2,i_spots))
code(action,Idle,6,b,
	task,i_spots,m_var.infoTableZone.totalSpots,m_var.p_totalSpots)
code(action,Idle,6,c,
	output,sOkInit,(m_pid,m_var.infoTableZone),0,0)
code(action,Idle,6,d,
	nextstate,(top,-1,top,3,))


code(dispatch,WaitSensorIR4,top,
	(sIR4_Zone,1))

code(fire,WaitSensorIR4,1,DELAYABLE,,,({0,0,0}),
	a,(),b,,,195)
code(action,WaitSensorIR4,1,a,
	input,sIR4_Zone,(m_var.SENDER,p1,pid))

code(action,WaitSensorIR4,1,b,
	nextstate,(top,-1,top,9,))


code(dispatch,WaitSensorIR2,top,
	(sIR2_Zone,1))

code(fire,WaitSensorIR2,1,DELAYABLE,,,({0,0,0}),
	a,(),b,,,203)
code(action,WaitSensorIR2,1,a,
	input,sIR2_Zone,(m_var.SENDER,p1,pid))

code(action,WaitSensorIR2,1,b,
	nextstate,(top,-1,top,7,))


code(dispatch,sEvaluatingFreeSpots,top,
	(,1,2))

code(fire,sEvaluatingFreeSpots,1,EAGER,,binop(eq,integer)(m_var.TmpfreeSpots,0),({0,0,0}),
	,((a)),b,,,209)
code(action,sEvaluatingFreeSpots,1,a,
	output,sEntered_Car,(m_pid,m_var.infoTableZone),0,0)
code(action,sEvaluatingFreeSpots,1,b,
	nextstate,(top,-1,top,3,))

code(fire,sEvaluatingFreeSpots,2,EAGER,,binop(gt,integer)(m_var.TmpfreeSpots,0),({0,0,0}),
	,((a),(b),(c)),d,,,212)
code(action,sEvaluatingFreeSpots,2,a,
	task,i_spots,m_var.TmpfreeSpots,binop(minus,integer)(m_var.TmpfreeSpots,1))
code(action,sEvaluatingFreeSpots,2,b,
	task,i_spots,m_var.infoTableZone.freeSpots,m_var.TmpfreeSpots)
code(action,sEvaluatingFreeSpots,2,c,
	output,sEntered_Car,(m_pid,m_var.infoTableZone),0,0)
code(action,sEvaluatingFreeSpots,2,d,
	nextstate,(top,-1,top,3,))


code(dispatch,VerifyIsaCarEntering,top,
	(sLoopInductive_Zone,1))

code(fire,VerifyIsaCarEntering,1,DELAYABLE,,,({0,0,0}),
	a,((b)),c,,,223)
code(action,VerifyIsaCarEntering,1,a,
	input,sLoopInductive_Zone,(m_var.SENDER,p1,pid))
code(action,VerifyIsaCarEntering,1,b,
	task,i_spots,m_var.TmpfreeSpots,m_var.infoTableZone.freeSpots)
code(action,VerifyIsaCarEntering,1,c,
	nextstate,(top,-1,top,6,))


code(dispatch,sEvaluatingTotalSpots,top,
	(,1,2))

code(fire,sEvaluatingTotalSpots,1,EAGER,,binop(eq,integer)(m_var.TmpfreeSpots,m_var.TmptotalSpots),({0,0,0}),
	,((a)),b,,,230)
code(action,sEvaluatingTotalSpots,1,a,
	output,sOut_Car,(m_pid,m_var.infoTableZone),0,0)
code(action,sEvaluatingTotalSpots,1,b,
	nextstate,(top,-1,top,3,))

code(fire,sEvaluatingTotalSpots,2,EAGER,,binop(lt,integer)(m_var.TmpfreeSpots,m_var.TmptotalSpots),({0,0,0}),
	,((a),(b),(c)),d,,,233)
code(action,sEvaluatingTotalSpots,2,a,
	task,i_spots,m_var.TmpfreeSpots,binop(plus,integer)(m_var.TmpfreeSpots,1))
code(action,sEvaluatingTotalSpots,2,b,
	task,i_spots,m_var.infoTableZone.freeSpots,m_var.TmpfreeSpots)
code(action,sEvaluatingTotalSpots,2,c,
	output,sOut_Car,(m_pid,m_var.infoTableZone),0,0)
code(action,sEvaluatingTotalSpots,2,d,
	nextstate,(top,-1,top,3,))


code(dispatch,VerifyIsaCarOut,top,
	(sLoopInductive_Zone,1))

code(fire,VerifyIsaCarOut,1,DELAYABLE,,,({0,0,0}),
	a,((b),(c)),d,,,244)
code(action,VerifyIsaCarOut,1,a,
	input,sLoopInductive_Zone,(m_var.SENDER,p1,pid))
code(action,VerifyIsaCarOut,1,b,
	task,i_spots,m_var.TmpfreeSpots,m_var.infoTableZone.freeSpots)
code(action,VerifyIsaCarOut,1,c,
	task,i_spots,m_var.TmptotalSpots,m_var.infoTableZone.totalSpots)
code(action,VerifyIsaCarOut,1,d,
	nextstate,(top,-1,top,8,))


code(instance_table,16,`
  {"top", 0, 1, 0 | CONTROL,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_pZone_instance::_top_dispatch},
  {"RTDS_START", 0, 1, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_pZone_instance::_RTDS_START_dispatch},
  {"sWait", 0, 2, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_pZone_instance::_sWait_dispatch},
  {"Idle", 0, 3, 0 | TSIG,
    {0,0,0,0,1,1,1,0,1,0,1,0,0,0,1},
    &if_pZone_instance::_Idle_dispatch},
  {"WaitSensorIR4", 0, 4, 0 | TSIG,
    {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    &if_pZone_instance::_WaitSensorIR4_dispatch},
  {"WaitSensorIR2", 0, 5, 0 | TSIG,
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
    &if_pZone_instance::_WaitSensorIR2_dispatch},
  {"sEvaluatingFreeSpots", 0, 6, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_pZone_instance::_sEvaluatingFreeSpots_dispatch},
  {"VerifyIsaCarEntering", 0, 7, 0 | TSIG,
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    &if_pZone_instance::_VerifyIsaCarEntering_dispatch},
  {"sEvaluatingTotalSpots", 0, 8, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_pZone_instance::_sEvaluatingTotalSpots_dispatch},
  {"VerifyIsaCarOut", 0, 9, 0 | TSIG,
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    &if_pZone_instance::_VerifyIsaCarOut_dispatch},
')

code(end_instance)


code(instance,RTDS_start_process,11,
	(),
	(),
	(),
	(top,integer),(top,-1,top,1,),
	())

code(dispatch,top,)

code(dispatch,RTDS_START,top,
	(,1))

code(fire,RTDS_START,1,EAGER,,if_boolean_true,({0,0,0}),
	,((a),(b)),c,,,254)
code(action,RTDS_START,1,a,
	fork,instance,pZone,(if_pid_nil),)
code(action,RTDS_START,1,b,
	kill,m_pid)
code(action,RTDS_START,1,c,
	stop)


code(instance_table,16,`
  {"top", 0, 1, 0 | CONTROL,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_RTDS_start_process_instance::_top_dispatch},
  {"RTDS_START", 0, 1, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_RTDS_start_process_instance::_RTDS_START_dispatch},
')

code(end_instance)



code(obsinstance,obsInitPid,12,(),
	(pidSender,pid,pidCtrl,pid,pidZone,pid,tmpVar,integer),
	(tmpVar,integer,0),
	(top,integer),(top,-1,top,1,))

code(dispatch,top,)

code(dispatch,RTDS_START,top,
	(,1))

code(fire,RTDS_START,1,LAZY,,if_boolean_true,({0,0,0}),
	,(),a,,,272)

code(action,RTDS_START,1,a,
	nextstate,(top,-1,top,3,))


code(dispatch,sOk,top,
	(,1))

code(fire,sOk,1,LAZY,,if_boolean_true,({0,0,0}),
	,((a)),b,,,278)
code(action,sOk,1,a,
	cut)
code(action,sOk,1,b,
	nextstate,(top,-1,top,6,))


code(dispatch,Idle,top,
	(,1,2))

code(fire,Idle,1,LAZY,,((if_obs_output(signal_name(sTemp), 0, (unsigned)-1, (unsigned)-1, (unsigned)-1))!= NULL && (signal_name(sTemp) == (if_obs_output(signal_name(sTemp), 0, (unsigned)-1, (unsigned)-1, (unsigned)-1))->getSid())),({0,0,0}),
	a,(),b,,,286)
code(action,Idle,1,a,
	matchoutput,sTemp,(m_var.pidSender,p1,pid),0,,&m_var.pidZone,NULL,NULL)

code(action,Idle,1,b,
	nextstate,(top,-1,top,4,))

code(fire,Idle,2,LAZY,,((if_obs_input(signal_name(sInitPidCtrl), (unsigned)-1))!= NULL && (signal_name(sInitPidCtrl) == (if_obs_input(signal_name(sInitPidCtrl), (unsigned)-1))->getSid())),({0,0,0}),
	a,((b)),c,,,288)
code(action,Idle,2,a,
	matchinput,sInitPidCtrl,(m_var.pidSender,p1,pid,m_var.pidCtrl,p2,pid),,&m_var.pidZone)
code(action,Idle,2,b,
	task,integer,m_var.tmpVar,1)
code(action,Idle,2,c,
	nextstate,(top,-1,top,3,))


code(dispatch,RTDS_decision_SYMB10,,
	(,1,2))

code(fire,RTDS_decision_SYMB10,1,LAZY,,unop(not,boolean)(binop(eq,integer)(m_var.tmpVar,1)),,
	,(),a,,,295)

code(action,RTDS_decision_SYMB10,1,a,
	nextstate,(top,-1,top,5,))

code(fire,RTDS_decision_SYMB10,2,LAZY,,binop(eq,integer)(m_var.tmpVar,1),,
	,((a)),b,,,298)
code(action,RTDS_decision_SYMB10,2,a,
	task,integer,m_var.tmpVar,0)
code(action,RTDS_decision_SYMB10,2,b,
	nextstate,(top,-1,top,2,))


code(dispatch,sError,top,
	(,1))

code(fire,sError,1,LAZY,,if_boolean_true,({0,0,0}),
	,((a)),b,,,305)
code(action,sError,1,a,
	cut)
code(action,sError,1,b,
	nextstate,(top,-1,top,6,))


code(dispatch,DEAD,top)

code(obsinstance_table,16,`
  {"top", 0, 1, 0 | CONTROL,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_top_dispatch},
  {"RTDS_START", 0, 1, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_RTDS_START_dispatch},
  {"sOk", 0, 2, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_sOk_dispatch},
  {"Idle", 0, 3, 0 | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_Idle_dispatch},
  {"RTDS_decision_SYMB10", 0, 4, 0 | UNSTABLE | TNONE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_RTDS_decision_SYMB10_dispatch},
  {"sError", 0, 5, 0 | TNONE | OERROR,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_sError_dispatch},
  {"DEAD", 0, 6, 0,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    &if_obsInitPid_instance::_DEAD_dispatch},
')

code(end_obsinstance)


define(`x_use_priorities', `1')
code(start,(),(RTDS_start_process,obsInitPid),,time)code(priority_rule_begin, 1)
code(priority_rule_null, 0)