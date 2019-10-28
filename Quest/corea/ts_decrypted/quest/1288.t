CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1288;
	title = 128802;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 128809;
				ctype = 1;
				idx = 7611203;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 128808;
				gtype = 2;
				area = 128801;
				goal = 128804;
				grade = 132203;
				rwd = 100;
				sort = 128805;
				stype = 1;
				taid = 1;
				title = 128802;
			}
			CDboTSActSToCEvt
			{
				dt2 = 128825;
				otype2 = 1;
				widx1 = 1;
				iidx0 = -1;
				otype1 = 1;
				widx2 = 1;
				dt0 = 128821;
				esctype = 0;
				iidx1 = -1;
				it1 = 128822;
				otype0 = 1;
				tidx2 = 7611206;
				dt1 = 128823;
				etype = 0;
				iidx2 = -1;
				it0 = 128820;
				taid = 3;
				tidx1 = 7611205;
				widx0 = 1;
				apptype = 0;
				eitype = 6;
				tidx0 = 7611204;
				ectype = -1;
				it2 = 128824;
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
		CDboTSContStart
		{
			cid = 0;
			stdiag = 128807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7611203;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
			CDboTSCheckClrQst
			{
				and = "1273;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 128808;
			gtype = 2;
			oklnk = 2;
			area = 128801;
			goal = 128804;
			sort = 128805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 128802;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 128814;
			nextlnk = 101;
			rwdtbl = 128801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7611203;
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
				itype = 6;
			}
		}
	}
}

