CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1083;
	title = 108302;

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
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 108307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1655201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 49;
				minlvl = 41;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 108314;
			nextlnk = 101;
			rwdtbl = 108301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1655201;
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
				conv = 108309;
				ctype = 1;
				idx = 1655201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 108308;
				m1fx = "-138.000000";
				m2fz = "-145.000000";
				m1fy = "0.000000";
				sort = 108305;
				m2widx = 4;
				grade = 132203;
				m0fx = "193.000000";
				m0ttip = 108315;
				m1widx = 4;
				rwd = 100;
				taid = 1;
				title = 108302;
				gtype = 5;
				area = 108301;
				goal = 108304;
				m0fz = "-284.000000";
				m0widx = 4;
				m1ttip = 108316;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "83.000000";
				m2fx = "18.000000";
				m2ttip = 108317;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 16;
				eitype = 0;
				idx0 = 2612103;
				cnt0 = 18;
				cnt2 = 1;
				ectype = -1;
				etype = 0;
				idx1 = 1651104;
				taid = 3;
				esctype = 0;
				idx2 = 1653100;
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
				eitype = 0;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 108308;
			gtype = 5;
			oklnk = 2;
			area = 108301;
			goal = 108304;
			sort = 108305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 108302;
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
				itype = 0;
			}
		}
	}
}

