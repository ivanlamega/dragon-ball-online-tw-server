CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 271;
	title = 27102;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActRegQInfo
			{
				cont = 27108;
				gtype = 1;
				area = 27101;
				goal = 27104;
				grade = 132203;
				rwd = 100;
				sort = 27105;
				stype = 1;
				taid = 1;
				title = 27102;
			}
			CDboTSActNPCConv
			{
				conv = 27109;
				ctype = 1;
				idx = 4751201;
				taid = 2;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 27107;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCRace
			{
				raceflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 4751201;
			}
			CDboTSCheckLvl
			{
				maxlvl = 21;
				minlvl = 13;
			}
			CDboTSCheckClrQst
			{
				and = "250;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
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
			cont = 27108;
			gtype = 1;
			oklnk = 2;
			area = 27101;
			goal = 27104;
			sort = 27105;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 27102;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 27114;
			nextlnk = 254;
			rwdtbl = 27101;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 6312101;
			}
		}
	}
}

