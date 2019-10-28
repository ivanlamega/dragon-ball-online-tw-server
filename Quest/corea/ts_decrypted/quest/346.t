CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 346;
	title = 34602;

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
				conv = 34609;
				ctype = 1;
				idx = 4751308;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 34608;
				gtype = 0;
				area = 34601;
				goal = 34604;
				grade = 132203;
				rwd = 100;
				sort = 34605;
				stype = 1;
				taid = 1;
				title = 34602;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 34614;
			nextlnk = 254;
			rwdtbl = 34601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511503;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 34607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4751308;
			}
			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSCheckLvl
			{
				maxlvl = 27;
				minlvl = 19;
			}
			CDboTSCheckClrQst
			{
				and = "338;";
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
			cont = 34608;
			gtype = 0;
			oklnk = 2;
			area = 34601;
			goal = 34604;
			sort = 34605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 34602;
		}
	}
}

