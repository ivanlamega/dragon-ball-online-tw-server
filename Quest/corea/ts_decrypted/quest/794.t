CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 794;
	title = 79402;

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
			stdiag = 79407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3613102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 35;
				minlvl = 27;
			}
			CDboTSCheckClrQst
			{
				and = "793;";
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
				conv = 79409;
				ctype = 1;
				idx = 3613102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 79408;
				m1fx = "7315.000000";
				area = 79401;
				goal = 79404;
				m0fz = "1620.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 79416;
				sort = 79405;
				stype = 2;
				m0fy = "0.000000";
				m1fz = "1620.000000";
				grade = 132203;
				m0fx = "7315.000000";
				m0ttip = 79415;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 79402;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 9;
				eitype = 1;
				idx0 = 573;
				cnt0 = 9;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 574;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 79414;
			nextlnk = 101;
			rwdtbl = 79401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3173201;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 79408;
			gtype = 2;
			oklnk = 2;
			area = 79401;
			goal = 79404;
			sort = 79405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 79402;
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
				icnt0 = 255;
				iidx1 = 574;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 573;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 79407;
			nolnk = 255;
			rm = 0;
			yeslnk = 2;
		}
	}
}

