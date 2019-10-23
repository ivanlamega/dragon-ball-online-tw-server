CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 405;
	title = 40502;

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
			stdiag = 40507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4152110;
			}
			CDboTSCheckLvl
			{
				maxlvl = 10;
				minlvl = 2;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 40514;
			nextlnk = 101;
			rwdtbl = 40501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4152110;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 634;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 635;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 633;
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
				conv = 40509;
				ctype = 1;
				idx = 4152110;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 40508;
				m1fx = "5780.000000";
				m2fz = "-3989.000000";
				m1fy = "0.000000";
				sort = 40505;
				m2widx = 1;
				grade = 132203;
				m0fx = "5914.000000";
				m0ttip = 40515;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 40502;
				gtype = 2;
				area = 40501;
				goal = 40504;
				m0fz = "-3903.000000";
				m0widx = 1;
				m1ttip = 40516;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-3906.000000";
				m2fx = "5844.000000";
				m2ttip = 40517;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 1;
				eitype = 3;
				idx0 = 633;
				cnt0 = 1;
				cnt2 = 1;
				ectype = -1;
				etype = 0;
				idx1 = 634;
				taid = 3;
				esctype = 0;
				idx2 = 635;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 40508;
			gtype = 2;
			oklnk = 2;
			area = 40501;
			goal = 40504;
			sort = 40505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 40502;
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
				itype = 3;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 40507;
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
				icnt2 = 255;
				iprob2 = "1.000000";
				icnt1 = 255;
				iidx0 = 633;
				iidx2 = 635;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
				icnt0 = 255;
				iidx1 = 634;
				iprob0 = "1.000000";
			}
		}
	}
}

