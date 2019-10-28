CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1525;
	title = 152502;

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
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 6;
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
				eitype = 6;
				esctype = 0;
				ectype = -1;
				etype = 1;
				taid = 1;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 152514;
			nextlnk = 101;
			rwdtbl = 152501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3331205;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 152508;
			gtype = 2;
			oklnk = 2;
			area = 152501;
			goal = 152504;
			sort = 152505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 152502;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 152509;
				ctype = 1;
				idx = 3331205;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 152508;
				gtype = 2;
				area = 152501;
				goal = 152504;
				grade = 132203;
				rwd = 100;
				sort = 152505;
				stype = 1;
				taid = 1;
				title = 152502;
			}
			CDboTSActSToCEvt
			{
				dt2 = 152525;
				otype2 = 7;
				widx1 = 1;
				iidx0 = -1;
				otype1 = 7;
				widx2 = 1;
				dt0 = -1;
				esctype = 0;
				iidx1 = -1;
				it1 = 152522;
				otype0 = 7;
				tidx2 = 973;
				dt1 = 152523;
				etype = 0;
				iidx2 = -1;
				it0 = -1;
				taid = 3;
				tidx1 = 972;
				widx0 = -1;
				apptype = 0;
				eitype = 6;
				tidx0 = -1;
				ectype = -1;
				it2 = 152524;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 152507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckLvl
			{
				maxlvl = 56;
				minlvl = 48;
			}
			CDboTSClickNPC
			{
				npcidx = 3331205;
			}
			CDboTSCheckClrQst
			{
				and = "1524;";
			}
		}
	}
}

