CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1554;
	title = 155402;

	CNtlTSGroup
	{
		gid = 0;

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
			stdiag = 155407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5312103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 155414;
			nextlnk = 101;
			rwdtbl = 155401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5312103;
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
				conv = 155409;
				ctype = 1;
				idx = 5312103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 155408;
				m1fx = "-2522.000000";
				area = 155401;
				goal = 155404;
				m0fz = "1271.000000";
				m0widx = 1;
				m1fy = "0.000000";
				m1ttip = 155416;
				sort = 155405;
				stype = 1;
				m0fy = "0.000000";
				m1fz = "1324.000000";
				grade = 132203;
				m0fx = "-1662.000000";
				m0ttip = 155415;
				m1widx = 1;
				rwd = 100;
				taid = 1;
				title = 155402;
				gtype = 2;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 8;
				eitype = 0;
				idx0 = 3501103;
				cnt0 = 8;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 3501111;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 155408;
			gtype = 2;
			oklnk = 2;
			area = 155401;
			goal = 155404;
			sort = 155405;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 155402;
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

