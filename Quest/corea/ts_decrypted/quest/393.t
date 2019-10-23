CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 393;
	title = 39302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "1;0;252;";
			type = 0;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 39314;
			nextlnk = 101;
			rwdtbl = 39301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6413105;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 1198;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 1199;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 39308;
			gtype = 2;
			oklnk = 2;
			area = 39301;
			goal = 39304;
			sort = 39305;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 39302;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 39307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 20;
				minlvl = 10;
			}
			CDboTSClickNPC
			{
				npcidx = 6413105;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
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
				conv = 39309;
				ctype = 1;
				idx = 6413105;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 39308;
				m1fx = "4235.000000";
				area = 39301;
				goal = 39304;
				m0fz = "-2229.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 39316;
				sort = 39305;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-2418.000000";
				grade = 132203;
				m0fx = "4256.000000";
				m0ttip = 39315;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 39302;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 1;
				idx0 = 1198;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 1199;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 1;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 39307;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iidx1 = 1199;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 1198;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
			}
		}
	}
}

