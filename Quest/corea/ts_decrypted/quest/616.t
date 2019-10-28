CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 616;
	title = 61602;

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
				conv = 61609;
				ctype = 1;
				idx = 4751107;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 61608;
				gtype = 1;
				area = 61601;
				goal = 61604;
				grade = 132203;
				rwd = 100;
				sort = 61605;
				stype = 2;
				taid = 1;
				title = 61602;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 61607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4751107;
			}
			CDboTSCheckLvl
			{
				maxlvl = 29;
				minlvl = 21;
			}
			CDboTSCheckClrQst
			{
				and = "615;";
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
			cont = 61608;
			gtype = 1;
			oklnk = 2;
			area = 61601;
			goal = 61604;
			sort = 61605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 61602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 61614;
			nextlnk = 254;
			rwdtbl = 61601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3031206;
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

