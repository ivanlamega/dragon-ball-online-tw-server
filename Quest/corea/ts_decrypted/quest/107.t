CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 107;
	title = 10702;

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
				tblidx = 7611101;
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
				conv = 10725;
				ctype = 1;
				idx = 7611101;
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
				conv = 10722;
				ctype = 1;
				idx = 7611101;
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
				conv = 10721;
				ctype = 1;
				idx = 7611101;
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
				taeid = 3;
				taid = 3;
				tceid = 11;
			}
			CDboTSActETimerE
			{
				taeid = 2;
				taid = 2;
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
				id = 4;
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
				time = 480000;
			}
			CDboTSActEscort
			{
				start = 1;
				tblidx = 7611101;
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
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "11;2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 10707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckLvl
			{
				maxlvl = 23;
				minlvl = 15;
			}
			CDboTSClickNPC
			{
				npcidx = 7611101;
			}
			CDboTSCheckClrQst
			{
				and = "106;";
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
				conv = 10709;
				ctype = 1;
				idx = 7611101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 10708;
				gtype = 2;
				area = 10701;
				goal = 10704;
				m0fz = "3509.750000";
				m0widx = 1;
				sort = 10705;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "5014.790039";
				m0ttip = 10715;
				rwd = 100;
				taid = 1;
				title = 10702;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 10714;
			nextlnk = 254;
			rwdtbl = 10701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "17;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8032105;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 10708;
			gtype = 2;
			oklnk = 2;
			area = 10701;
			goal = 10704;
			sort = 10705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 10702;
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
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckDistWithNPC
			{
				dist = "30.000000";
				idxlist = "7611101;";
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
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
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
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckNPCDead
			{
				idxlist = "7611101;";
			}
		}
	}
}

