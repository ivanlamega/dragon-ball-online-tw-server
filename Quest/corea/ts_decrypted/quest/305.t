CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 305;
	title = 30502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 16;
			elnk = 255;
			nextlnk = 17;
			prelnk = "15;";

			CDboTSActEscort
			{
				start = 0;
				tblidx = 3143101;
				tsshare = 1;
				etype = 1;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 17;
			elnk = 255;
			nextlnk = 100;
			prelnk = "16;";

			CDboTSActNPCConv
			{
				conv = 30509;
				ctype = 1;
				idx = 3143101;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 13;
			elnk = 255;
			nextlnk = 14;
			prelnk = "12;";

			CDboTSActNPCConv
			{
				conv = 30509;
				ctype = 1;
				idx = 3143101;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 12;
			elnk = 255;
			nextlnk = 13;
			prelnk = "11;";

			CDboTSActTWaitTS
			{
				taid = 1;
				time = 10000;
			}
		}
		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 11;
			prelnk = "4;";

			CDboTSActTWaitTS
			{
				taid = 1;
				time = 10000;
			}
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 255;
			nextlnk = 4;
			prelnk = "2;";

			CDboTSActTWaitTS
			{
				taid = 1;
				time = 2000;
			}
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 5;
			prelnk = "3;";

			CDboTSActNPCConv
			{
				conv = 30509;
				ctype = 1;
				idx = 3143101;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 15;
			elnk = 255;
			nextlnk = 16;
			prelnk = "14;";

			CDboTSActETimerE
			{
				taeid = 4;
				taid = 4;
				tceid = 11;
			}
			CDboTSActETimerE
			{
				taeid = 2;
				taid = 2;
				tceid = 11;
			}
			CDboTSActETimerE
			{
				taeid = 3;
				taid = 3;
				tceid = 11;
			}
		}
		CDboTSContGCond
		{
			cid = 14;
			prelnk = "13;";
			nolnk = 255;
			rm = 0;
			yeslnk = 15;

			CDboTSRcvSvrEvt
			{
				id = 9;
			}
		}
		CDboTSContGAct
		{
			cid = 11;
			elnk = 252;
			nextlnk = 12;
			prelnk = "5;";

			CDboTSActETimerS
			{
				sort = 1;
				taid = 3;
				tgid = 12;
				time = 2000;
			}
			CDboTSActETimerS
			{
				sort = 0;
				taid = 4;
				tgid = 1;
				time = 600000;
			}
			CDboTSActEscort
			{
				start = 1;
				tblidx = 3143101;
				tsshare = 1;
				etype = 1;
				taid = 1;
			}
			CDboTSActETimerS
			{
				sort = 1;
				taid = 2;
				tgid = 11;
				time = 2000;
			}
			CDboTSActSendSvrEvt
			{
				id = 8;
				tblidx = 4752104;
				stradius = 0;
				stype = 0;
				taid = 5;
				ttype = 255;
				type = 0;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "11;2;";
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 30507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3143101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 23;
				minlvl = 15;
			}
			CDboTSCheckClrQst
			{
				and = "304;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 30509;
				ctype = 1;
				idx = 3143101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 30508;
				gtype = 1;
				area = 30501;
				goal = 30504;
				m0fz = "-2364.649902";
				m0widx = 1;
				sort = 30505;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "4778.250000";
				m0ttip = 30515;
				rwd = 100;
				taid = 1;
				title = 30502;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 30514;
			nextlnk = 254;
			rwdtbl = 30501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "17;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4752101;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 30508;
			gtype = 1;
			oklnk = 2;
			area = 30501;
			goal = 30504;
			sort = 30505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 30502;
		}
	}
	CNtlTSGroup
	{
		gid = 11;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActTSState
			{
				state = 2;
				taid = 1;
				type = 0;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 30507;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckDistWithNPC
			{
				dist = "30.000000";
				idxlist = "3143101;";
			}
		}
	}
	CNtlTSGroup
	{
		gid = 12;

		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActTSState
			{
				state = 2;
				taid = 1;
				type = 0;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 30507;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckNPCDead
			{
				idxlist = "3143101;";
			}
		}
	}
	CNtlTSGroup
	{
		gid = 1;

		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 2;
			prelnk = "0;";

			CDboTSActTSState
			{
				state = 2;
				taid = 1;
				type = 0;
			}
		}
		CDboTSContEnd
		{
			cid = 2;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 30507;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

