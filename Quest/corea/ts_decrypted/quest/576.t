CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 576;
	title = 57602;

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
				conv = 57609;
				ctype = 1;
				idx = 3142109;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 57608;
				gtype = 0;
				area = 57601;
				goal = 57604;
				grade = 132203;
				rwd = 100;
				sort = 57605;
				stype = 1;
				taid = 1;
				title = 57602;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 57607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 4;
			}
			CDboTSClickNPC
			{
				npcidx = 3142109;
			}
			CDboTSCheckLvl
			{
				maxlvl = 28;
				minlvl = 20;
			}
			CDboTSCheckClrQst
			{
				and = "562;570;";
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 57608;
			gtype = 0;
			oklnk = 2;
			area = 57601;
			goal = 57604;
			sort = 57605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 57602;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 57614;
			nextlnk = 254;
			rwdtbl = 57601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 8031301;
			}
		}
	}
}

