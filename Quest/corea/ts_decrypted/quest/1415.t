CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1415;
	title = 141502;

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
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 141507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3242108;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 141508;
			gtype = 2;
			oklnk = 2;
			area = 141501;
			goal = 141504;
			sort = 141505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 141502;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 141509;
				ctype = 1;
				idx = 3242108;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 141508;
				m1fx = "3446.000000";
				m2fz = "4849.000000";
				m1fy = "0.000000";
				sort = 141505;
				m2widx = 1;
				grade = 132203;
				m0fx = "3433.000000";
				m0ttip = 141515;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 141502;
				gtype = 2;
				area = 141501;
				goal = 141504;
				m0fz = "4812.000000";
				m0widx = 1;
				m1ttip = 141516;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "4754.000000";
				m2fx = "3454.000000";
				m2ttip = 141517;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 833;
				cnt0 = 18;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 141514;
			nextlnk = 101;
			rwdtbl = 141501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3242108;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 24;
				iidx = 833;
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

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;2;";
			type = 0;
		}
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 254;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 833;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 833;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 141507;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

