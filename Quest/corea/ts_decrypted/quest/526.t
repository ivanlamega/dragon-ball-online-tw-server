CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 526;
	title = 52602;

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
				conv = 52609;
				ctype = 1;
				idx = 3273101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 52608;
				gtype = 0;
				area = 52601;
				goal = 52604;
				grade = 132203;
				rwd = 100;
				sort = 52605;
				stype = 2;
				taid = 1;
				title = 52602;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 52607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 3273101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 24;
				minlvl = 16;
			}
			CDboTSCheckClrQst
			{
				and = "508;";
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
			cont = 52608;
			gtype = 0;
			oklnk = 2;
			area = 52601;
			goal = 52604;
			sort = 52605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 52602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 52614;
			nextlnk = 254;
			rwdtbl = 52601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3172104;
			}
		}
	}
}

