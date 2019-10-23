CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1104;
	title = 110402;

	CNtlTSGroup
	{
		gid = 0;

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
			stdiag = 110407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3031212;
			}
			CDboTSCheckLvl
			{
				maxlvl = 50;
				minlvl = 42;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 110414;
			nextlnk = 101;
			rwdtbl = 110401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031212;
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
				conv = 110409;
				ctype = 1;
				idx = 3031212;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 110408;
				m1fx = "1785.000000";
				m2fz = "1997.000000";
				m1fy = "0.000000";
				sort = 110405;
				m2widx = 1;
				grade = 132203;
				m0fx = "1627.000000";
				m0ttip = 110415;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 110402;
				gtype = 1;
				area = 110401;
				goal = 110404;
				m0fz = "1993.000000";
				m0widx = 1;
				m1ttip = 110415;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "1978.000000";
				m2fx = "1827.000000";
				m2ttip = 110415;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 319;
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
			cont = 110408;
			gtype = 1;
			oklnk = 2;
			area = 110401;
			goal = 110404;
			sort = 110405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 110402;
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
				iidx = 319;
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
				iidx0 = 319;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 110407;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

