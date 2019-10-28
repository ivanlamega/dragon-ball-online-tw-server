CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1843;
	title = 184302;

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
				itype = 0;
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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 184309;
				ctype = 1;
				idx = 3612102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 184308;
				m1fx = "707.000000";
				area = 184301;
				goal = 184304;
				m0fz = "-1473.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 184316;
				sort = 184305;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-1345.000000";
				grade = 132203;
				m0fx = "742.000000";
				m0ttip = 184315;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 184302;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 15;
				eitype = 0;
				idx0 = 5812201;
				cnt0 = 25;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 5812301;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "252;0;1;";
			type = 0;
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
			cont = 184308;
			gtype = 2;
			oklnk = 2;
			area = 184301;
			goal = 184304;
			sort = 184305;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 184302;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 184307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3612102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 46;
				minlvl = 38;
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
			desc = 184314;
			nextlnk = 101;
			rwdtbl = 184301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3612102;
			}
		}
	}
}

