CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 915;
	title = 91502;

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
				tidx0 = 588;
				ectype = -1;
				etype = 0;
				iidx0 = -1;
				it0 = 91520;
				taid = 1;
				widx0 = 1;
				dt0 = 91521;
				esctype = 0;
				otype0 = 7;
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
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 91514;
			nextlnk = 101;
			rwdtbl = 91501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5061112;
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
				conv = 91509;
				ctype = 1;
				idx = 2951104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 91508;
				gtype = 1;
				area = 91501;
				goal = 91504;
				grade = 132203;
				rwd = 100;
				sort = 91505;
				stype = 1;
				taid = 1;
				title = 91502;
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
			cont = 91508;
			gtype = 1;
			oklnk = 2;
			area = 91501;
			goal = 91504;
			sort = 91505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 91502;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 91507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2951104;
			}
			CDboTSCheckLvl
			{
				maxlvl = 39;
				minlvl = 31;
			}
			CDboTSCheckClrQst
			{
				and = "913;";
			}
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

