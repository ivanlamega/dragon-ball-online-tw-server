CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1272;
	title = 127202;

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
				conv = 127209;
				ctype = 1;
				idx = 2611102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 127208;
				gtype = 1;
				area = 127201;
				goal = 127204;
				grade = 132203;
				rwd = 100;
				sort = 127205;
				stype = 2;
				taid = 1;
				title = 127202;
			}
			CDboTSActSToCEvt
			{
				dt2 = 127225;
				otype2 = 1;
				widx1 = 1;
				iidx0 = -1;
				otype1 = 1;
				widx2 = 1;
				dt0 = 127221;
				esctype = 0;
				iidx1 = -1;
				it1 = 127222;
				otype0 = 1;
				tidx2 = 1551107;
				dt1 = 127223;
				etype = 0;
				iidx2 = -1;
				it0 = 127220;
				taid = 3;
				tidx1 = 1752103;
				widx0 = 1;
				apptype = 0;
				eitype = 6;
				tidx0 = 4071107;
				ectype = -1;
				it2 = 127224;
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
			desc = 127214;
			nextlnk = 101;
			rwdtbl = 127201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2611102;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 127207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2611102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 52;
				minlvl = 44;
			}
			CDboTSCheckClrQst
			{
				and = "1271;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 127208;
			gtype = 1;
			oklnk = 2;
			area = 127201;
			goal = 127204;
			sort = 127205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 127202;
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
	}
}

