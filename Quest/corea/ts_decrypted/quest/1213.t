CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1213;
	title = 121302;

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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 121308;
			gtype = 2;
			oklnk = 2;
			area = 121301;
			goal = 121304;
			sort = 121305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 121302;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 121309;
				ctype = 1;
				idx = 2801108;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 121308;
				m1fx = "1949.000000";
				area = 121301;
				goal = 121304;
				m0fz = "2956.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 121316;
				sort = 121305;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "2993.000000";
				grade = 132203;
				m0fx = "1700.000000";
				m0ttip = 121315;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 121302;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 20;
				eitype = 1;
				idx0 = 158;
				cnt0 = 20;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 159;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 121314;
			nextlnk = 101;
			rwdtbl = 121301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2801108;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 20;
				iidx = 159;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 20;
				iidx = 158;
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
			stdiag = 121307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2801108;
			}
			CDboTSCheckLvl
			{
				maxlvl = 51;
				minlvl = 43;
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
				itype = 1;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 121307;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
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
				iidx1 = 159;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 158;
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
	}
}

