CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 788;
	title = 78802;

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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 78809;
				ctype = 1;
				idx = 6312109;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 78808;
				m1fx = "5291.000000";
				m2fz = "1440.000000";
				m1fy = "0.000000";
				sort = 78805;
				m2widx = 1;
				grade = 132203;
				m0fx = "5415.000000";
				m0ttip = 78815;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 78802;
				gtype = 2;
				area = 78801;
				goal = 78804;
				m0fz = "1486.000000";
				m0widx = 1;
				m1ttip = 78816;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "1367.000000";
				m2fx = "5260.000000";
				m2ttip = 78817;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 8;
				eitype = 1;
				idx0 = 568;
				cnt0 = 8;
				cnt2 = 8;
				ectype = -1;
				etype = 0;
				idx1 = 569;
				taid = 3;
				esctype = 0;
				idx2 = 570;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 78814;
			nextlnk = 101;
			rwdtbl = 78801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6312109;
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
			stdiag = 78807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6312109;
			}
			CDboTSCheckLvl
			{
				maxlvl = 34;
				minlvl = 26;
			}
			CDboTSCheckClrQst
			{
				and = "787;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 78808;
			gtype = 2;
			oklnk = 2;
			area = 78801;
			goal = 78804;
			sort = 78805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 78802;
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
				itype = 1;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt2 = 255;
				iprob2 = "1.000000";
				icnt1 = 255;
				iidx0 = 568;
				iidx2 = 570;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
				icnt0 = 255;
				iidx1 = 569;
				iprob0 = "1.000000";
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 78807;
			nolnk = 255;
			rm = 0;
			yeslnk = 2;
		}
	}
}

