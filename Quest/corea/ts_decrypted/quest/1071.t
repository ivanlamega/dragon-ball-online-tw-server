CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1071;
	title = 107102;

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
				apptype = 0;
				eitype = 6;
				tidx0 = 3101101;
				ectype = -1;
				etype = 0;
				iidx0 = -1;
				it0 = 107120;
				taid = 1;
				widx0 = 1;
				dt0 = 107121;
				esctype = 0;
				otype0 = 1;
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
			stdiag = 107107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 6312105;
			}
			CDboTSCheckLvl
			{
				maxlvl = 49;
				minlvl = 41;
			}
			CDboTSCheckClrQst
			{
				and = "1061;";
			}
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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 107109;
				ctype = 1;
				idx = 6312105;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 107108;
				gtype = 2;
				area = 107101;
				goal = 107104;
				grade = 132203;
				rwd = 100;
				sort = 107105;
				stype = 2;
				taid = 1;
				title = 107102;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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
			cont = 107108;
			gtype = 2;
			oklnk = 2;
			area = 107101;
			goal = 107104;
			sort = 107105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 107102;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 107114;
			nextlnk = 101;
			rwdtbl = 107101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6312105;
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

