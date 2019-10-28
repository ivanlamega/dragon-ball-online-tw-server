CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 864;
	title = 86402;

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
		CDboTSContGCond
		{
			cid = 4;
			prelnk = "100;3;";
			nolnk = 255;
			rm = 1;
			yeslnk = 5;

			CDboTSClickNPC
			{
				npcidx = 3173201;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 16;
				iidx = 601;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 16;
				iidx = 600;
			}
		}
		CDboTSContUnifiedNarration
		{
			cancellnk = 100;
			cid = 5;
			idx = 8643;
			lilnk = 255;
			oklnk = 100;
			prelnk = "4;";
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
			stdiag = 86407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3173201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 38;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "863;";
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
				conv = 86409;
				ctype = 1;
				idx = 3173201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 86408;
				m1fx = "615.000000";
				m2fz = "1558.000000";
				m1fy = "0.000000";
				sort = 86405;
				m2widx = 1;
				grade = 132203;
				m0fx = "592.000000";
				m0ttip = 86415;
				m1widx = 3;
				rwd = 100;
				taid = 1;
				title = 86402;
				gtype = 3;
				area = 86401;
				goal = 86404;
				m0fz = "-428.000000";
				m0widx = 3;
				m1ttip = 86416;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "-206.000000";
				m2fx = "7448.000000";
				m2ttip = 86417;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 16;
				eitype = 1;
				idx0 = 600;
				cnt0 = 16;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 601;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 4;
			cid = 100;
			desc = 86414;
			nextlnk = 101;
			rwdtbl = 86401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "5;5;";
			usetbl = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 86408;
			gtype = 3;
			oklnk = 2;
			area = 86401;
			goal = 86404;
			sort = 86405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 86402;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

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
				iidx1 = 601;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 600;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 86407;
			nolnk = 255;
			rm = 0;
			yeslnk = 2;
		}
	}
}

