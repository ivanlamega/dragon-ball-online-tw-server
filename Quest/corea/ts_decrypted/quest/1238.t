CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1238;
	title = 123802;

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
			stdiag = 123807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4372101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 51;
				minlvl = 43;
			}
			CDboTSCheckClrQst
			{
				and = "1235;";
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
				conv = 123809;
				ctype = 1;
				idx = 4372101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 123808;
				m1fx = "2480.000000";
				m2fz = "3428.000000";
				m1fy = "0.000000";
				sort = 123805;
				m2widx = 1;
				grade = 132203;
				m0fx = "2335.000000";
				m0ttip = 123815;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 123802;
				gtype = 2;
				area = 123801;
				goal = 123804;
				m0fz = "3533.000000";
				m0widx = 1;
				m1ttip = 123815;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "3528.000000";
				m2fx = "2372.000000";
				m2ttip = 123815;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 3;
				idx0 = 800;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 123814;
			nextlnk = 101;
			rwdtbl = 123801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372101;
			}
			CDboTSCheckQItem
			{
				ct = 0;
				icnt = 6;
				iidx = 800;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 123808;
			gtype = 2;
			oklnk = 2;
			area = 123801;
			goal = 123804;
			sort = 123805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 123802;
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
				iidx0 = 800;
				taid = 1;
				type = 1;
			}
		}
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
				iidx = 800;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 123807;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

