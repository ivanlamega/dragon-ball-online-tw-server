CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1354;
	title = 135402;

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
			stdiag = 135407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 1551103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 54;
				minlvl = 46;
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
				conv = 135409;
				ctype = 1;
				idx = 1551103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 135408;
				m1fx = "2734.000000";
				m2fz = "5636.000000";
				m1fy = "0.000000";
				sort = 135405;
				m2widx = 1;
				grade = 132203;
				m0fx = "974.000000";
				m0ttip = 135415;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 135402;
				gtype = 2;
				area = 135401;
				goal = 135404;
				m0fz = "3818.000000";
				m0widx = 1;
				m1ttip = 135416;
				m2fy = "0.000000";
				stype = 1;
				m0fy = "0.000000";
				m1fz = "5658.000000";
				m2fx = "2521.000000";
				m2ttip = 135417;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 1;
				idx0 = 867;
				cnt0 = 27;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 135414;
			nextlnk = 101;
			rwdtbl = 135401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1551103;
			}
			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 27;
				iidx = 867;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 135408;
			gtype = 2;
			oklnk = 2;
			area = 135401;
			goal = 135404;
			sort = 135405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 135402;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 135407;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
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
				iidx = 867;
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
				iidx0 = 867;
				taid = 1;
				type = 1;
			}
		}
	}
}

