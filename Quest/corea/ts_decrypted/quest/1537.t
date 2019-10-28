CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1537;
	title = 153702;

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
			stdiag = 153707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5061110;
			}
			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 153714;
			nextlnk = 101;
			rwdtbl = 153701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5061110;
			}
			CDboTSCheckSToCEvt
			{
				itype = 3;
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
				conv = 153709;
				ctype = 1;
				idx = 5061110;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 153708;
				m1fx = "-2626.000000";
				m2fz = "2379.000000";
				m1fy = "0.000000";
				sort = 153705;
				m2widx = 1;
				grade = 132203;
				m0fx = "-2768.000000";
				m0ttip = 153715;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 153702;
				gtype = 2;
				area = 153701;
				goal = 153704;
				m0fz = "2368.000000";
				m0widx = 1;
				m1ttip = 153715;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "2226.000000";
				m2fx = "-2186.000000";
				m2ttip = 153715;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 935;
				cnt0 = 6;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
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
			cont = 153708;
			gtype = 2;
			oklnk = 2;
			area = 153701;
			goal = 153704;
			sort = 153705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 153702;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 153707;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 935;
				taid = 1;
				type = 1;
			}
		}
	}
}

