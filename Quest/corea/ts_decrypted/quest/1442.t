CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1442;
	title = 144202;

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
				conv = 144209;
				ctype = 1;
				idx = 3143113;
				taid = 2;
			}
			CDboTSActSToCEvt
			{
				dt2 = 144225;
				otype2 = 7;
				widx1 = 2;
				iidx0 = -1;
				otype1 = 7;
				widx2 = 2;
				dt0 = 144221;
				esctype = 0;
				iidx1 = -1;
				it1 = 144222;
				otype0 = 7;
				tidx2 = 17;
				dt1 = 144223;
				etype = 0;
				iidx2 = -1;
				it0 = 144220;
				taid = 3;
				tidx1 = 15;
				widx0 = 2;
				apptype = 0;
				eitype = 6;
				tidx0 = 16;
				ectype = -1;
				it2 = 144224;
			}
			CDboTSActRegQInfo
			{
				cont = 144208;
				gtype = 3;
				area = 144201;
				goal = 144204;
				grade = 132203;
				rwd = 100;
				sort = 144205;
				stype = 2;
				taid = 1;
				title = 144202;
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
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 144208;
			gtype = 3;
			oklnk = 2;
			area = 144201;
			goal = 144204;
			sort = 144205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 144202;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 144207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3143113;
			}
			CDboTSCheckLvl
			{
				maxlvl = 55;
				minlvl = 47;
			}
			CDboTSCheckClrQst
			{
				and = "1431;";
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 144214;
			nextlnk = 101;
			rwdtbl = 144201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3143113;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
	}
}

