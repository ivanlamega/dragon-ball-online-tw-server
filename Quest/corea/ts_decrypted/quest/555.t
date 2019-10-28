CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 555;
	title = 55502;

	CNtlTSGroup
	{
		gid = 11;

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
			stdiag = 55507;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckDistWithNPC
			{
				dist = "30.000000";
				idxlist = "2611201;";
			}
		}
	}
	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 6;
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
				conv = 55509;
				ctype = 1;
				idx = 2611201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 55508;
				gtype = 1;
				area = 55501;
				goal = 55504;
				grade = 132203;
				rwd = 100;
				sort = 55505;
				stype = 2;
				taid = 1;
				title = 55502;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				eitype = 6;
				tidx0 = 2611101;
				ectype = -1;
				etype = 0;
				iidx0 = -1;
				it0 = 55533;
				taid = 3;
				widx0 = 1;
				dt0 = 55530;
				esctype = 0;
				otype0 = 1;
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
			cont = 55508;
			gtype = 1;
			oklnk = 2;
			area = 55501;
			goal = 55504;
			sort = 55505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 55502;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 55507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 27;
				minlvl = 19;
			}
			CDboTSClickNPC
			{
				npcidx = 2611201;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 55514;
			nextlnk = 254;
			rwdtbl = 55501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2611201;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 12;

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
			stdiag = 55507;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckNPCDead
			{
				idxlist = "2611201;";
			}
		}
	}
}

