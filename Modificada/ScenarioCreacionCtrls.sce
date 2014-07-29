run
send2pid -1 3 sSetUpFreeSpot |{param1|=0|,param2|=0|,param3|=10|}
send2pid -1 3 sSetUpTotalSpot |{param1|=0|,param2|=0|,param3|=20|}
send2pid -1 3 sAddZone |{param1|=0|,param2|=30|,param3|=20|}
send2pid -1 3 sCreateCtrlZone
send2pid -1 3 sAddZone |{param1|=1|,param2|=10|,param3|=10|}
send2pid -1 5 sIR1_Zone
send2pid -1 5 sIR2_Zone
send2pid -1 5 sLoopInductive_Zone
send2pid -1 3 sReqInfoCtrlZone
stop
include C:/Documents and Settings/Virtual Machine/Mis documentos/Dropbox/TD_JPGR/VERSION MODIFICADA/ModificadaFebrero252014/Scenario1.sce
