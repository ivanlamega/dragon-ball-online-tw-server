CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 95;
	title = 9502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 9509;
				ctype = 1;
				idx = 3331201;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 9508;
				gtype = 1;
				area = 9501;
				goal = 9504;
				grade = 132203;
				rwd = 100;
				sort = 9505;
				stype = 2;
				taid = 1;
				title = 9502;
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
			cont = 9508;
			gtype = 1;
			oklnk = 2;
			area = 9501;
			goal = 9504;
			sort = 9505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 9502;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 9514;
			nextlnk = 254;
			rwdtbl = 9501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8032105;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 9507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 3;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 3331201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 22;
				minlvl = 14;
			}
			CDboTSCheckClrQst
			{
				and = "94;";
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
			prelnk = "100;";
			type = 1;
		}
	}
}

