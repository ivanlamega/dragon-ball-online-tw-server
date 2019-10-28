CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 711;
	title = 71102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 17;
			elnk = 255;
			nextlnk = 100;
			prelnk = "15;";

			CDboTSActWorldPlayScript
			{
				sid = 711;
				start = 0;
				taid = 2;
				uof = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 252;
			nextlnk = 5;
			prelnk = "2;";

			CDboTSActWorldPlayScript
			{
				sid = 711;
				start = 1;
				taid = 2;
				uof = 1;
			}
		}
		CDboTSContGCond
		{
			cid = 6;
			prelnk = "5;";
			nolnk = 255;
			rm = 0;
			yeslnk = 15;

			CDboTSRcvSvrEvt
			{
				id = 58;
			}
		}
		CDboTSContGAct
		{
			cid = 15;
			elnk = 255;
			nextlnk = 17;
			prelnk = "6;";

			CDboTSActETimerE
			{
				taeid = 1;
				taid = 1;
				tceid = 5;
			}
			CDboTSActETimerE
			{
				taeid = 2;
				taid = 2;
				tceid = 5;
			}
		}
		CDboTSContGAct
		{
			cid = 5;
			elnk = 252;
			nextlnk = 6;
			prelnk = "3;";

			CDboTSActETimerS
			{
				sort = 1;
				taid = 1;
				tgid = 11;
				time = 2000;
			}
			CDboTSActETimerS
			{
				sort = 1;
				taid = 2;
				tgid = 12;
				time = 2000;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 71108;
				gtype = 3;
				area = 71101;
				goal = 71104;
				grade = 132203;
				rwd = 100;
				sort = 71105;
				stype = 2;
				taid = 1;
				title = 71102;
			}
			CDboTSActNPCConv
			{
				conv = 71109;
				ctype = 1;
				idx = 4754201;
				taid = 2;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 71114;
			nextlnk = 254;
			rwdtbl = 71101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "17;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5061106;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 71107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4754201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 32;
				minlvl = 24;
			}
			CDboTSCheckClrQst
			{
				and = "682;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 71108;
			gtype = 3;
			oklnk = 2;
			area = 71101;
			goal = 71104;
			sort = 71105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 71102;
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
			prelnk = "3;5;2;";
		}
	}
	CNtlTSGroup
	{
		gid = 11;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 71107;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckDistWithNPC
			{
				dist = "30.000000";
				idxlist = "4754201;";
			}
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
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
	}
	CNtlTSGroup
	{
		gid = 12;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 71107;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckNPCDead
			{
				idxlist = "4754201;";
			}
		}
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
	}
}

