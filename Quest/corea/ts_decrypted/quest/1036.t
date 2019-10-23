CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1036;
	title = 103602;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 103607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6412102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 48;
				minlvl = 40;
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
				eitype = 3;
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
			cont = 103608;
			gtype = 1;
			oklnk = 2;
			area = 103601;
			goal = 103604;
			sort = 103605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 103602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 103614;
			nextlnk = 101;
			rwdtbl = 103601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3142201;
			}
			CDboTSCheckSToCEvt
			{
				itype = 3;
			}
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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 103609;
				ctype = 1;
				idx = 6412102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 103608;
				m1fx = "138.000000";
				area = 103601;
				goal = 103604;
				m0fz = "819.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 103616;
				sort = 103605;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "972.000000";
				grade = 132203;
				m0fx = "128.000000";
				m0ttip = 103615;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 103602;
				gtype = 1;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 3;
				idx0 = 763;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 764;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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
				icnt0 = 255;
				iidx1 = 764;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 763;
				iprob1 = "1.000000";
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
			stdiag = 103607;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

