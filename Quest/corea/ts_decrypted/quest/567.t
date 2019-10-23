CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 567;
	title = 56702;

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
			stdiag = 56707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1591102;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 28;
				minlvl = 20;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 56714;
			nextlnk = 101;
			rwdtbl = 56701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1591102;
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
				conv = 56709;
				ctype = 1;
				idx = 1591102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 56708;
				m1fx = "6754.000000";
				area = 56701;
				goal = 56704;
				m0fz = "87.000000";
				m0widx = 7;
				m1fy = "0.000000";
				m1ttip = 56716;
				sort = 56705;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-4270.000000";
				grade = 132203;
				m0fx = "403.000000";
				m0ttip = 56715;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 56702;
				gtype = 3;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 5722101;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 56708;
			gtype = 3;
			oklnk = 2;
			area = 56701;
			goal = 56704;
			sort = 56705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 56702;
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

