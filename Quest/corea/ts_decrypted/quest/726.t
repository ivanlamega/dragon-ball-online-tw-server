CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 726;
	title = 72602;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 5;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 72609;
				ctype = 1;
				idx = 3332102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 72608;
				gtype = 2;
				area = 72601;
				goal = 72604;
				m0fz = "2154.000000";
				m0widx = 1;
				sort = 72605;
				stype = 2;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "5643.000000";
				m0ttip = 72615;
				rwd = 100;
				taid = 1;
				title = 72602;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 2133104;
				cnt0 = 8;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
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
			stdiag = 72607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3332103;
			}
			CDboTSCheckClrQst
			{
				and = "725;";
			}
			CDboTSCheckLvl
			{
				maxlvl = 32;
				minlvl = 24;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 72614;
			nextlnk = 101;
			rwdtbl = 72601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "5;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3181201;
			}
		}
		CDboTSContGCond
		{
			cid = 5;
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
			cont = 72608;
			gtype = 2;
			oklnk = 2;
			area = 72601;
			goal = 72604;
			sort = 72605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 72602;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
	CNtlTSGroup
	{
		gid = 21;
	}
}

