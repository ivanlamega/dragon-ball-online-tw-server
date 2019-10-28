CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1283;
	title = 128302;

	CNtlTSGroup
	{
		gid = 0;

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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 128308;
			gtype = 2;
			oklnk = 2;
			area = 128301;
			goal = 128304;
			sort = 128305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 128302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 128314;
			nextlnk = 101;
			rwdtbl = 128301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1551107;
			}
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
			stdiag = 128307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1551107;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
			CDboTSCheckClrQst
			{
				and = "1281;1282;";
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
				conv = 128309;
				ctype = 1;
				idx = 1551107;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 128308;
				m1fx = "1959.000000";
				m2fz = "4282.000000";
				m1fy = "0.000000";
				sort = 128305;
				m2widx = 1;
				grade = 132203;
				m0fx = "1880.000000";
				m0ttip = 128315;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 128302;
				gtype = 2;
				area = 128301;
				goal = 128304;
				m0fz = "4276.000000";
				m0widx = 1;
				m1ttip = 128316;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "3141.000000";
				m2fx = "1669.000000";
				m2ttip = 128317;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 10;
				eitype = 0;
				idx0 = 7112105;
				cnt0 = 10;
				cnt2 = 10;
				ectype = -1;
				etype = 0;
				idx1 = 7111103;
				taid = 3;
				esctype = 0;
				idx2 = 7113103;
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
				itype = 0;
			}
		}
	}
}

