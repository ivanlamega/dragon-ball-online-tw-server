CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 351;
	title = 35102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 10;
			elnk = 255;
			nextlnk = 100;
			prelnk = "9;";

			CDboTSActTWaitTS
			{
				taid = 1;
				time = 6000;
			}
		}
		CDboTSContGAct
		{
			cid = 9;
			elnk = 255;
			nextlnk = 10;
			prelnk = "8;";

			CDboTSActEscort
			{
				start = 0;
				tblidx = 4511305;
				tsshare = 1;
				etype = 1;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 8;
			elnk = 255;
			nextlnk = 9;
			prelnk = "7;";

			CDboTSActETimerE
			{
				taeid = 3;
				taid = 2;
				tceid = 6;
			}
			CDboTSActETimerE
			{
				taeid = 2;
				taid = 1;
				tceid = 6;
			}
			CDboTSActETimerE
			{
				taeid = 4;
				taid = 3;
				tceid = 6;
			}
		}
		CDboTSContGCond
		{
			cid = 7;
			prelnk = "6;";
			nolnk = 255;
			rm = 0;
			yeslnk = 8;

			CDboTSRcvSvrEvt
			{
				id = 15;
			}
		}
		CDboTSContGAct
		{
			cid = 6;
			elnk = 252;
			nextlnk = 7;
			prelnk = "5;";

			CDboTSActETimerS
			{
				sort = 0;
				taid = 2;
				tgid = 1;
				time = 300000;
			}
			CDboTSActETimerS
			{
				sort = 1;
				taid = 3;
				tgid = 11;
				time = 2000;
			}
			CDboTSActETimerS
			{
				sort = 1;
				taid = 4;
				tgid = 12;
				time = 2000;
			}
			CDboTSActEscort
			{
				start = 1;
				tblidx = 4511305;
				tsshare = 1;
				etype = 1;
				taid = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 6;
			prelnk = "4;";

			CDboTSActTWaitTS
			{
				taid = 1;
				time = 5000;
			}
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 5;
			prelnk = "3;";

			CDboTSActSendSvrEvt
			{
				id = 14;
				tblidx = 4511305;
				stradius = 0;
				stype = 0;
				taid = 1;
				ttype = 255;
				type = 0;
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
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 35109;
				ctype = 1;
				idx = 4511305;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 35108;
				gtype = 2;
				area = 35101;
				goal = 35104;
				m0fz = "-1835.000000";
				m0widx = 1;
				sort = 35105;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "4697.000000";
				m0ttip = 35115;
				rwd = 100;
				taid = 1;
				title = 35102;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 35107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4511305;
			}
			CDboTSCheckPCCls
			{
				clsflg = 16;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 27;
				minlvl = 19;
			}
			CDboTSCheckClrQst
			{
				and = "350;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 35108;
			gtype = 2;
			oklnk = 2;
			area = 35101;
			goal = 35104;
			sort = 35105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 35102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 35114;
			nextlnk = 254;
			rwdtbl = 35101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "10;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4751401;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "6;2;";
		}
	}
	CNtlTSGroup
	{
		gid = 1;

		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 253;
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
			cid = 253;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 35107;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
	CNtlTSGroup
	{
		gid = 11;

		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 253;
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
			stdiag = 35107;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckNPCDead
			{
				idxlist = "4511305;";
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
			nextlnk = 253;
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
			cid = 253;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 35107;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckDistWithNPC
			{
				dist = "30.000000";
				idxlist = "4511305;";
			}
		}
	}
}

