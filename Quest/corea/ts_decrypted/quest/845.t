CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 845;
	title = 84502;

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
			stdiag = 84507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1653107;
			}
			CDboTSCheckLvl
			{
				maxlvl = 37;
				minlvl = 29;
			}
			CDboTSCheckClrQst
			{
				and = "844;";
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
				conv = 84509;
				ctype = 1;
				idx = 1653107;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 84508;
				m1fx = "429.000000";
				m2fz = "1558.000000";
				m1fy = "0.000000";
				sort = 84505;
				m2widx = 1;
				grade = 132203;
				m0fx = "349.000000";
				m0ttip = 84515;
				m1widx = 3;
				rwd = 100;
				taid = 1;
				title = 84502;
				gtype = 3;
				area = 84501;
				goal = 84504;
				m0fz = "91.000000";
				m0widx = 3;
				m1ttip = 84516;
				m2fy = "0.000000";
				stype = 2;
				m0fy = "0.000000";
				m1fz = "82.000000";
				m2fx = "7448.000000";
				m2ttip = 84517;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 14;
				eitype = 1;
				idx0 = 593;
				cnt0 = 14;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 594;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 84514;
			nextlnk = 101;
			rwdtbl = 84501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1654107;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 84508;
			gtype = 3;
			oklnk = 2;
			area = 84501;
			goal = 84504;
			sort = 84505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 84502;
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
				iidx1 = 594;
				iprob0 = "1.000000";
				icnt1 = 255;
				iidx0 = 593;
				iprob1 = "1.000000";
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 84507;
			nolnk = 255;
			rm = 0;
			yeslnk = 2;
		}
	}
}

