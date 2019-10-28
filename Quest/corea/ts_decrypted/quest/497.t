CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 497;
	title = 49702;

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
				conv = 49709;
				ctype = 1;
				idx = 3221101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 49708;
				gtype = 0;
				area = 49701;
				goal = 49704;
				grade = 132203;
				rwd = 100;
				sort = 49705;
				stype = 2;
				taid = 1;
				title = 49702;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 49708;
			gtype = 0;
			oklnk = 2;
			area = 49701;
			goal = 49704;
			sort = 49705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 49702;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 49714;
			nextlnk = 254;
			rwdtbl = 49701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4151202;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 49707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3221101;
			}
			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSCheckLvl
			{
				maxlvl = 23;
				minlvl = 15;
			}
			CDboTSCheckClrQst
			{
				and = "491;496;";
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
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
	}
}

