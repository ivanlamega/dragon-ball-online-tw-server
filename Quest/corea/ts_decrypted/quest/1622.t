CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1622;
	title = 162202;

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
			stdiag = 162207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6412107;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
			CDboTSCheckClrQst
			{
				and = "1621;";
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 162209;
				ctype = 1;
				idx = 6412107;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 162208;
				m1fx = "-1647.000000";
				m2fz = "893.000000";
				m1fy = "0.000000";
				sort = 162205;
				m2widx = 1;
				grade = 132203;
				m0fx = "-1115.000000";
				m0ttip = 162215;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 162202;
				gtype = 3;
				area = 162201;
				goal = 162204;
				m0fz = "1121.000000";
				m0widx = 1;
				m1ttip = 162216;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "1005.000000";
				m2fx = "-1250.000000";
				m2ttip = 162217;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 10;
				eitype = 1;
				idx0 = 1039;
				cnt0 = 10;
				cnt2 = 10;
				ectype = -1;
				etype = 0;
				idx1 = 1040;
				taid = 3;
				esctype = 0;
				idx2 = 1041;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 162214;
			nextlnk = 101;
			rwdtbl = 162201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6412107;
			}
			CDboTSCheckSToCEvt
			{
				itype = 1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 162208;
			gtype = 3;
			oklnk = 2;
			area = 162201;
			goal = 162204;
			sort = 162205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 162202;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				taid = 1;
				type = 1;
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
			stdiag = 162207;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

