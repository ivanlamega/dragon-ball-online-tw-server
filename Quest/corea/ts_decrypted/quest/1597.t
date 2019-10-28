CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1597;
	title = 159702;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGCond
		{
			cid = 4;
			prelnk = "3;";
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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 159709;
				ctype = 1;
				idx = 5063106;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 159708;
				gtype = 2;
				area = 159701;
				goal = 159704;
				grade = 132203;
				rwd = 100;
				sort = 159705;
				stype = 1;
				taid = 1;
				title = 159702;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 159707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5063106;
			}
			CDboTSCheckLvl
			{
				maxlvl = 57;
				minlvl = 49;
			}
			CDboTSCheckClrQst
			{
				and = "1592;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 159708;
			gtype = 2;
			oklnk = 2;
			area = 159701;
			goal = 159704;
			sort = 159705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 159702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 159714;
			nextlnk = 101;
			rwdtbl = 159701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5063106;
			}
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 255;
			nextlnk = 4;
			prelnk = "2;";

			CDboTSActSToCEvt
			{
				dt2 = 159725;
				otype2 = 1;
				widx1 = 1;
				iidx0 = -1;
				otype1 = 1;
				widx2 = 1;
				dt0 = 159721;
				esctype = 0;
				iidx1 = -1;
				it1 = 159722;
				otype0 = 1;
				tidx2 = 8511115;
				dt1 = 159723;
				etype = 0;
				iidx2 = -1;
				it0 = 159720;
				taid = 1;
				tidx1 = 7073108;
				widx0 = 1;
				apptype = 0;
				eitype = 6;
				tidx0 = 5061110;
				ectype = -1;
				it2 = 159724;
			}
		}
	}
}

