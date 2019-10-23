CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1246;
	title = 124602;

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
			stdiag = 124607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1351113;
			}
			CDboTSCheckLvl
			{
				maxlvl = 51;
				minlvl = 43;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 124614;
			nextlnk = 101;
			rwdtbl = 124601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1351113;
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
				conv = 124609;
				ctype = 1;
				idx = 1351113;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 124608;
				m1fx = "2190.000000";
				area = 124601;
				goal = 124604;
				m0fz = "3554.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 124616;
				sort = 124605;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "3633.000000";
				grade = 132203;
				m0fx = "2207.000000";
				m0ttip = 124615;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 124602;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 18;
				eitype = 0;
				idx0 = 8312200;
				cnt0 = 18;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 8312300;
				taid = 3;
				esctype = 0;
				idx2 = -1;
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
			cont = 124608;
			gtype = 2;
			oklnk = 2;
			area = 124601;
			goal = 124604;
			sort = 124605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 124602;
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

