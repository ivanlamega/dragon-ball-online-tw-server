CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 771;
	title = 77102;

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
				eitype = 0;
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
			stdiag = 77107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7132101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 33;
				minlvl = 25;
			}
			CDboTSCheckClrQst
			{
				and = "770;";
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
				conv = 77109;
				ctype = 1;
				idx = 7132101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 77108;
				m1fx = "5103.000000";
				area = 77101;
				goal = 77104;
				m0fz = "-714.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 77116;
				sort = 77105;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "-714.000000";
				grade = 132203;
				m0fx = "5103.000000";
				m0ttip = 77115;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 77102;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 14;
				eitype = 0;
				idx0 = 1712104;
				cnt0 = 14;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 4512100;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 77114;
			nextlnk = 101;
			rwdtbl = 77101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7132101;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 77108;
			gtype = 2;
			oklnk = 2;
			area = 77101;
			goal = 77104;
			sort = 77105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 77102;
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
				itype = 0;
			}
		}
	}
}

