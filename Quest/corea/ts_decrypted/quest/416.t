CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 416;
	title = 41602;

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
				conv = 41609;
				ctype = 1;
				idx = 7711101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 41608;
				gtype = 0;
				area = 41601;
				goal = 41604;
				grade = 132203;
				rwd = 100;
				sort = 41605;
				stype = 1;
				taid = 1;
				title = 41602;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 41607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckPCCls
			{
				clsflg = 32;
			}
			CDboTSClickNPC
			{
				npcidx = 7711101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 12;
				minlvl = 4;
			}
			CDboTSCheckClrQst
			{
				and = "404;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 41608;
			gtype = 0;
			oklnk = 2;
			area = 41601;
			goal = 41604;
			sort = 41605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 41602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 41614;
			nextlnk = 254;
			rwdtbl = 41601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4141102;
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

