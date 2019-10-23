CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1336;
	title = 133602;

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
				conv = 133609;
				ctype = 1;
				idx = 5313101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 133608;
				gtype = 0;
				area = 133601;
				goal = 133604;
				grade = 132203;
				rwd = 100;
				sort = 133605;
				stype = 2;
				taid = 1;
				title = 133602;
			}
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
			desc = 133614;
			nextlnk = 254;
			rwdtbl = 133601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372211;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 133608;
			gtype = 0;
			oklnk = 2;
			area = 133601;
			goal = 133604;
			sort = 133605;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 133602;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 133607;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5313101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 53;
				minlvl = 45;
			}
			CDboTSCheckClrQst
			{
				and = "1335;";
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

