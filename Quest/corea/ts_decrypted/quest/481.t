CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 481;
	title = 48102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 3;
			elnk = 255;
			nextlnk = 4;
			prelnk = "2;";

			CDboTSActSToCEvt
			{
				dt2 = 48135;
				otype2 = 1;
				widx1 = 1;
				iidx0 = -1;
				otype1 = 1;
				widx2 = 1;
				dt0 = 48133;
				esctype = 0;
				iidx1 = -1;
				it1 = 48131;
				otype0 = 1;
				tidx2 = 5592102;
				dt1 = 48134;
				etype = 0;
				iidx2 = -1;
				it0 = 48130;
				taid = 1;
				tidx1 = 3221101;
				widx0 = 1;
				apptype = 0;
				eitype = 6;
				tidx0 = 7141126;
				ectype = -1;
				it2 = 48132;
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

			CDboTSActRegQInfo
			{
				cont = 48108;
				gtype = 2;
				area = 48101;
				goal = 48104;
				grade = 132203;
				rwd = 100;
				sort = 48105;
				stype = 2;
				taid = 1;
				title = 48102;
			}
			CDboTSActNPCConv
			{
				conv = 48109;
				ctype = 1;
				idx = 4192101;
				taid = 2;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 48108;
			gtype = 2;
			oklnk = 2;
			area = 48101;
			goal = 48104;
			sort = 48105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 48102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 48114;
			nextlnk = 101;
			rwdtbl = 48101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4192101;
			}
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
			stdiag = 48107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 4192101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 21;
				minlvl = 13;
			}
			CDboTSCheckClrQst
			{
				and = "478;";
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
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
	}
}

