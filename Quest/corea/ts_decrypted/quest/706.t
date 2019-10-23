CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 706;
	title = 70602;

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
				conv = 70609;
				ctype = 1;
				idx = 3032103;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 70608;
				gtype = 1;
				area = 70601;
				goal = 70604;
				grade = 132203;
				rwd = 100;
				sort = 70605;
				stype = 2;
				taid = 1;
				title = 70602;
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
			cont = 70608;
			gtype = 1;
			oklnk = 2;
			area = 70601;
			goal = 70604;
			sort = 70605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 70602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 70614;
			nextlnk = 254;
			rwdtbl = 70601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3032102;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 70607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 1;
			}
			CDboTSClickNPC
			{
				npcidx = 3032103;
			}
			CDboTSCheckLvl
			{
				maxlvl = 32;
				minlvl = 24;
			}
			CDboTSCheckClrQst
			{
				and = "705;";
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

