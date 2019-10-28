CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 188;
	title = 18802;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSSearchQuest
			{
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
				conv = 18809;
				ctype = 1;
				idx = 4181101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 18808;
				gtype = 1;
				area = 18801;
				goal = 18804;
				grade = 132203;
				rwd = 100;
				sort = 18805;
				stype = 2;
				taid = 1;
				title = 18802;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 18814;
			nextlnk = 254;
			rwdtbl = 18801;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4181101;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 18808;
			gtype = 1;
			oklnk = 2;
			area = 18801;
			goal = 18804;
			sort = 18805;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 18802;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 18807;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4181101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 10;
				minlvl = 2;
			}
			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSCheckClrQst
			{
				and = "6;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
	}
}

