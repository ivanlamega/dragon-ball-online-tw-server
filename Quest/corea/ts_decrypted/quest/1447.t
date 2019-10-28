CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1447;
	title = 144702;

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
			stdiag = 144707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
			CDboTSClickNPC
			{
				npcidx = 2803101;
			}
			CDboTSCheckClrQst
			{
				and = "1446;";
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
				conv = 144709;
				ctype = 1;
				idx = 2803101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 144708;
				m1fx = "989.000000";
				area = 144701;
				goal = 144704;
				m0fz = "-366.000000";
				m0widx = 2;
				m1fy = "0.000000";
				m1ttip = 144716;
				sort = 144705;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-184.000000";
				grade = 132203;
				m0fx = "924.000000";
				m0ttip = 144715;
				m1widx = 2;
				rwd = 100;
				taid = 1;
				title = 144702;
				gtype = 3;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 20;
				eitype = 0;
				idx0 = 6613304;
				cnt0 = 20;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 4813201;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 144714;
			nextlnk = 101;
			rwdtbl = 144701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2803101;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 144708;
			gtype = 3;
			oklnk = 2;
			area = 144701;
			goal = 144704;
			sort = 144705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 144702;
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
	}
}

