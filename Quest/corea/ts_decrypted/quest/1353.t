CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1353;
	title = 135302;

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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 135307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1111115;
			}
			CDboTSCheckLvl
			{
				maxlvl = 54;
				minlvl = 46;
			}
			CDboTSCheckClrQst
			{
				and = "1352;";
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
				conv = 135309;
				ctype = 1;
				idx = 1111115;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 135308;
				m1fx = "2703.000000";
				m2fz = "5706.000000";
				m1fy = "0.000000";
				sort = 135305;
				m2widx = 1;
				grade = 132203;
				m0fx = "1068.000000";
				m0ttip = 135315;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 135302;
				gtype = 2;
				area = 135301;
				goal = 135304;
				m0fz = "3698.000000";
				m0widx = 1;
				m1ttip = 135316;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "5726.000000";
				m2fx = "2562.000000";
				m2ttip = 135317;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 9;
				eitype = 0;
				idx0 = 9413100;
				cnt0 = 9;
				cnt2 = 9;
				ectype = -1;
				etype = 0;
				idx1 = 9413200;
				taid = 3;
				esctype = 0;
				idx2 = 6612104;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 135314;
			nextlnk = 101;
			rwdtbl = 135301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1111115;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 135308;
			gtype = 2;
			oklnk = 2;
			area = 135301;
			goal = 135304;
			sort = 135305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 135302;
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

