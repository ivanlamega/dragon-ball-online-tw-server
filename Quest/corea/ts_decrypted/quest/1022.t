CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1022;
	title = 102202;

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
			stdiag = 102207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2801103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 46;
				minlvl = 38;
			}
			CDboTSCheckClrQst
			{
				and = "1021;";
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
				conv = 102209;
				ctype = 1;
				idx = 2801103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 102208;
				m1fx = "146.000000";
				area = 102201;
				goal = 102204;
				m0fz = "191.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 102216;
				sort = 102205;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "222.000000";
				grade = 132203;
				m0fx = "682.000000";
				m0ttip = 102215;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 102202;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 20;
				eitype = 0;
				idx0 = 5611112;
				cnt0 = 20;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 6612203;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 102214;
			nextlnk = 101;
			rwdtbl = 102201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2801103;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 102208;
			gtype = 2;
			oklnk = 2;
			area = 102201;
			goal = 102204;
			sort = 102205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 102202;
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

