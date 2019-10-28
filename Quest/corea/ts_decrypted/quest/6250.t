CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6250;
	title = 625002;

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
				itype = 0;
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
			stdiag = 625007;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3221210;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 45;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 625014;
			nextlnk = 101;
			rwdtbl = 625001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 1653110;
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
				conv = 625009;
				ctype = 1;
				idx = 3221210;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 625008;
				gtype = 5;
				area = 625001;
				goal = 625004;
				grade = 132203;
				rwd = 100;
				sort = 625005;
				stype = 2;
				taid = 1;
				title = 625002;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 6692100;
				cnt0 = 1;
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
			cont = 625008;
			gtype = 5;
			oklnk = 2;
			area = 625001;
			goal = 625004;
			sort = 625005;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 625002;
		}
	}
}

